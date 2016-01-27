#include "AttackState.h"

// Spy
#include "SpyNPC.h"

const float AttackState::S_MISSING_TIMER = 6.f;
const float AttackState::S_TIME_TILL_ATTACK = 2.f;

AttackState::AttackState() : FSMState(), m_attackTimer(S_TIME_TILL_ATTACK), m_missingTimer(0.f), m_reached(false), m_recordPoint(true)
{
	m_stateName = "Attack state";
}


AttackState::~AttackState()
{
}

void AttackState::Init(NPC * FSMOwner)
{
	FSMState::Init(FSMOwner);

	Guard* g = dynamic_cast<Guard*>(m_FSMOwner);

	// Check if the NPC is legit
	if (!g)
	{
		return;
	}

	// Set up the child state
}

void AttackState::Init(FSMState * stateOwner)
{
	// Attach the handle to the state owner
	FSMState::Init(stateOwner);

	// Get the actual NPC-type pointer
	Guard* g = dynamic_cast<Guard*>(m_FSMOwner);

	// Check if the NPC is legit
	if (!g)
	{
		return;
	}
}

void AttackState::Update(double dt)
{
	FSMState::Update(dt);

	Guard* g = dynamic_cast<Guard*>(m_FSMOwner);

	// Check if the NPC is legit
	if (!g)
	{
		return;
	}

	if (g->GetAttacked() && g->GetKnockedOut())
	{
		if (g->GetLastTarget())
		{
			g->GetLastTarget()->SetTargetted(false); // Tell spy that guard no longer has sight on it
		}
		else if (g->GetTarget())
		{
			g->GetTarget()->SetTargetted(false); // Tell spy that guard no longer has sight on it
		}
		g->SetMoveSpeed(Guard::S_GUARD_PATROL_SPEED);
		changeState(new AttackedState());
		return;
	}

	if (!g->GetTarget()) // Target missing
	{
		m_missingTimer += dt;
		if (g->GetLastTarget())
		{
			//g->GetLastTarget()->SetTargetted(false); // Tell spy that guard no longer has sight on it
		}
		if (!m_reached)
		{
			if (m_recordPoint)
			{
				g->AddToFallback(g->GetTransform().Translation);
				m_recordPoint = false;
			}
			moveToLastSeen(dt);
		}
		else
		{
			g->SetMoveSpeed(Guard::S_GUARD_PATROL_SPEED);
			g->GetView()->SetScale(Vector2(g->GetDefaultViewRadius() * 2.f, g->GetDefaultViewRadius() * 2.f));
			g->UpdateViewPosition();
			changeState(new PatrolState());
			return;
		}
	}
	else // Target still in sight
	{
		m_missingTimer = 0.f;
		m_recordPoint = true;
		g->GetTarget()->SetTargetted(true); // Tell spy that guard spotted it
		m_attackTimer += dt;
		if (m_attackTimer >= S_TIME_TILL_ATTACK)
		{
			int killChance = Math::RandIntMinMax(1, 100);
			if (killChance < 70) // % chance to kill spy
			{
				g->GetTarget()->Kill();
				g->GetTarget()->SetTargetted(false);
				g->SetMoveSpeed(Guard::S_GUARD_PATROL_SPEED);
				g->GetView()->SetScale(Vector2(g->GetDefaultViewRadius() * 2.f, g->GetDefaultViewRadius() * 2.f));
				g->UpdateViewPosition();

				changeState(new PatrolState());
				return;
			}
			m_attackTimer = 0.f;
		}
	}

	if (m_missingTimer >= S_MISSING_TIMER) // Can't find target for a period of time
	{
		if (g->GetLastTarget())
		{
			g->GetLastTarget()->SetTargetted(false); // Tell spy that guard no longer has sight on it
		}
		changeState(new PatrolState());
		g->GetView()->SetScale(Vector2(g->GetDefaultViewRadius() * 2.f, g->GetDefaultViewRadius() * 2.f));
		g->UpdateViewPosition();
		return;
	}
}

void AttackState::Exit(void)
{
}

void AttackState::moveToLastSeen(double dt)
{
	Guard* g = dynamic_cast<Guard*>(m_FSMOwner);

	// Check if the NPC is legit
	if (!g)
	{
		return;
	}

	g->SetLookDir((g->GetLastSeen() - g->GetTransform().Translation).Normalized());

	float distFromLastSeen = (g->GetTransform().Translation - g->GetLastSeen()).LengthSquared();
	float movement = g->GetMoveSpeed() * dt;
	float movementSquared = movement * movement;

	if (movementSquared > distFromLastSeen) // Walk past waypoint
	{
		g->SetPos(g->GetLastSeen());
		g->UpdateViewPosition();
		m_reached = true;
	}
	else
	{
		g->SetPos(g->GetTransform().Translation + (g->GetLookDir() * movement));
		g->UpdateViewPosition();
	}
}
