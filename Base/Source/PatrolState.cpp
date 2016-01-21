#include "PatrolState.h"

const float PatrolState::S_TIME_TO_CHANGE_SPEED_MIN = 5.f; // Minimum 5 seconds for guard to changing speed
const float PatrolState::S_TIME_TO_CHANGE_SPEED_MAX = 20.f; // Maximum 20 seconds for guard to change speed
const float PatrolState::S_TIME_TO_REST_MIN = S_TIME_TO_CHANGE_SPEED_MIN * 1.5f;
const float PatrolState::S_TIME_TO_REST_MAX = S_TIME_TO_CHANGE_SPEED_MAX * 1.5f;

PatrolState::PatrolState() : FSMState(), m_patrolTimer(0.f), m_rest(false), m_slowDownTimer(0.f), m_justSlowDown(false), m_timeToChangeSpeed(0.f), m_timeToRest(0.f)
{
	m_stateName = "Patrol State";
}


PatrolState::~PatrolState()
{
}

void PatrolState::Init(NPC * FSMOwner)
{
	FSMState::Init(FSMOwner);
	
	Guard* g = dynamic_cast<Guard*>(m_FSMOwner);

	// Check if the NPC is legit
	if (!g)
	{
		return;
	}

	m_patrolTimer = m_slowDownTimer = 0.f;
	m_rest = m_justSlowDown = false;
	m_timeToChangeSpeed = Math::RandFloatMinMax(S_TIME_TO_CHANGE_SPEED_MIN, S_TIME_TO_CHANGE_SPEED_MAX);
	m_timeToRest = Math::RandFloatMinMax(S_TIME_TO_REST_MIN, S_TIME_TO_REST_MAX);
	if (g->GetFallbacks().size() > 0 && g->GetFallbacks().top() != g->GetTransform().Translation) // Fallback required
	{
		g->SetLookDir((g->GetFallbacks().top() - g->GetTransform().Translation).Normalized());
	}
	else if (g->GetTransform().Translation != g->GetDestination()->GetPos())
	{
		g->SetLookDir((g->GetDestination()->GetPos() - g->GetTransform().Translation).Normalized());
	}

	// Set up the child state
}

void PatrolState::Init(FSMState * stateOwner)
{
	// Attach the handle to the state owner
	FSMState::Init(stateOwner);

	// Get the actual NPC-type pointer
	Guard* npc = dynamic_cast<Guard*>(m_FSMOwner);

	// Check if the NPC is legit
	if (!npc)
	{
		return;
	}
}

void PatrolState::Update(double dt)
{
	// Run the child state
	FSMState::Update(dt);

	// Check if npc-type pointer is real
	Guard* g = dynamic_cast<Guard*>(m_FSMOwner);
	if (!g)
	{
		return;
	}

	// Trigger Conditions here
	if (g->GetTarget()) // Target exists
	{
		g->GetView()->SetScale(Vector2(g->GetDefaultViewRadius() * 3.f, g->GetDefaultViewRadius() * 3.f));
		g->UpdateViewPosition();
		changeState(new AttackState());
		return; // Break out of this function
	}

	if (g->GetAttacked()) // For both attacked and knockout
	{
		changeState(new AttackedState());
		return; // Break out of this function
	}

	if (m_rest) // Trigger rest
	{
		changeState(new SlackState());
		return; // Break out of this function
	}

	m_patrolTimer += (float)dt;
	if (m_justSlowDown) // Slowed down
	{
		m_slowDownTimer += (float)dt;
	}
	if (m_patrolTimer >= m_timeToChangeSpeed && !m_rest) // Determine to slow down or not
	{
		int changeSpeed_OR_rest; // 0 - Nothing | 1 - Change speed | 2 - Rest
		if (m_patrolTimer >= m_timeToRest) // Can rest, choose whether to rest or slow down
		{
			changeSpeed_OR_rest = Math::RandIntMinMax(E_NOTHING, E_REST);
		}
		else
		{
			changeSpeed_OR_rest = Math::RandIntMinMax(E_NOTHING, E_CHANG_SPEED);;
		}

		// Check if just slow down
		if (changeSpeed_OR_rest == E_CHANG_SPEED && m_justSlowDown && m_slowDownTimer < m_timeToChangeSpeed)
		{
			changeSpeed_OR_rest = E_NOTHING;
		}

		if (changeSpeed_OR_rest == E_REST)
		{
			float restChance = Math::RandFloatMinMax(0.f, 120.f); // Max of 120 seconds before being forced to rest
			if (restChance <= m_patrolTimer - m_timeToRest) // Rest
			{
				m_rest = true;
			}

		}
		else if (changeSpeed_OR_rest == E_CHANG_SPEED) // Used for slow down and speed up
		{
			float speedChangeChance = Math::RandFloatMinMax(0.f, 10.f); // Max of 10 seconds before being forced to slow down
			if (speedChangeChance <= m_patrolTimer - m_timeToChangeSpeed) // Slow down
			{
				if (g->GetMoveSpeed() == Guard::S_GUARD_DRAGGING_SPEED) // Already slowed down, change to normal speed
				{
					g->SetMoveSpeed(Guard::S_GUARD_PATROL_SPEED);
					m_patrolTimer = 0.f;
					m_justSlowDown = false;
					m_slowDownTimer = 0.f;
				}
				else
				{
					g->SetMoveSpeed(Guard::S_GUARD_DRAGGING_SPEED);
					m_justSlowDown = true;
					m_slowDownTimer = 0.f;
					// Do not reset timer to give guard a chance to rest
				}
			}
		}
	}

	if (g->GetDestination()->GetPos() == g->GetTransform().Translation) // Reached destination
	{
		if (!m_rest)
		{
			if (g->GetFallbacks().size() <= 0)
			{
				calculateNewDestination();
			}
		}
		else
		{
			changeState(new SlackState());
			return;
		}
	}
	else // Move towards destination
	{
		if (g->GetFallbacks().size() > 0)
		{
			moveToFallback(dt);
		}
		else
		{
			moveToDestination(dt);
		}
	}
}

void PatrolState::Exit(void)
{
	FSMState::Exit();
}

void PatrolState::calculateNewDestination()
{
	Guard* g = dynamic_cast<Guard*>(m_FSMOwner);
	if (g->GetDestination()->GetNext().size() <= 0) // No next points
	{
		return;
	}

	bool done = false;
	while (!done)
	{
		int random = rand() % g->GetDestination()->GetNext().size();
		if (g->GetDestination()->GetNext()[random] != g->GetPrevLocation())
		{
			g->SetPrevLocation(g->GetDestination());
			g->SetDestination(g->GetDestination()->GetNext()[random]);
			g->GetLookDir() = (g->GetDestination()->GetPos() - g->GetTransform().Translation).Normalized();
			done = true;
		}
	}
}

bool PatrolState::moveToDestination(double dt)
{
	Guard* g = dynamic_cast<Guard*>(m_FSMOwner);
	float distFromWaypoint = (g->GetTransform().Translation - g->GetDestination()->GetPos()).LengthSquared();
	float movement = g->GetMoveSpeed() * dt;
	float movementSquared = movement * movement;

	if (movementSquared > distFromWaypoint) // Walk past waypoint
	{
		g->SetPos(g->GetDestination()->GetPos());
		g->UpdateViewPosition();
	}
	else
	{
		g->SetPos(g->GetTransform().Translation + (g->GetLookDir() * movement));
		g->UpdateViewPosition();
	}
	return true;
}

bool PatrolState::moveToFallback(double dt)
{
	Guard* g = dynamic_cast<Guard*>(m_FSMOwner);

	if (!g)
	{
		return false;
	}

	if (g->GetFallbacks().size() <= 0)
	{
		return false;
	}

	float distFromWaypoint = (g->GetTransform().Translation - g->GetFallbacks().top()).LengthSquared();
	float movement = g->GetMoveSpeed() * dt;
	float movementSquared = movement * movement;

	if (movementSquared > distFromWaypoint) // Walk past waypoint
	{
		g->SetPos(g->GetFallbacks().top());
		g->UpdateViewPosition();
		g->GetFallbacks().pop();
		if (g->GetFallbacks().size() > 0)
		{
			if (g->GetFallbacks().top() != g->GetTransform().Translation)
			{
				g->SetLookDir((g->GetFallbacks().top() - g->GetTransform().Translation).Normalized());
			}
			else
			{
				g->GetFallbacks().pop();
				if (g->GetFallbacks().size() > 0)
				{
					if (g->GetFallbacks().top() != g->GetTransform().Translation)
					{
						g->SetLookDir((g->GetFallbacks().top() - g->GetTransform().Translation).Normalized());
					}
				}
			}
		}
		else
		{
			if (g->GetTransform().Translation != g->GetDestination()->GetPos())
			{
				g->SetLookDir((g->GetDestination()->GetPos() - g->GetTransform().Translation).Normalized());
			}
			else
			{
				calculateNewDestination();
			}
		}
	}
	else
	{
		g->SetPos(g->GetTransform().Translation + (g->GetLookDir() * movement));
		g->UpdateViewPosition();
	}
	return true;
}