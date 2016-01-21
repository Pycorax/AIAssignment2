#include "SlackState.h"

const float SlackState::S_REST_MAX_TIME = 5.f;

SlackState::SlackState() : FSMState(), m_slackTimer(0.f)
{
	SCALE_DOWN_VIEW[SLACK_REST] = 0.5f;
	SCALE_DOWN_VIEW[SLACK_SLEEP] = 0.f;
	m_stateName = "Slack State";
}


SlackState::~SlackState()
{
}

void SlackState::Init(NPC * FSMOwner)
{
	FSMState::Init(FSMOwner);
	m_slackTimer = 0.f;

	Guard* g = dynamic_cast<Guard*>(m_FSMOwner);

	// Check if the NPC is legit
	if (!g)
	{
		return;
	}

	int random = Math::RandIntMinMax(SLACK_REST, SLACK_SLEEP);
	m_currentState = (E_SLACK_TYPES)random;
	g->GetView()->SetScale(g->GetView()->GetTransform().Scale * SCALE_DOWN_VIEW[m_currentState]); // When slacking, smaller view
	g->UpdateViewPosition();

	// Set up the child state
}

void SlackState::Init(FSMState * stateOwner)
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

void SlackState::Update(double dt)
{
	FSMState::Update(dt);
	Guard* g = dynamic_cast<Guard*>(m_FSMOwner);
	if (!g)
	{
		return;
	}

	if (g->GetAttacked())
	{
		g->GetView()->SetScale(Vector2(g->GetDefaultViewRadius() * 2.f, g->GetDefaultViewRadius() * 2.f)); // Set view scale back to default
		g->UpdateViewPosition();
		changeState(new AttackedState());
		return; // Break out of this function
	}

	if (m_currentState == SLACK_REST && g->GetAttacker())
	{
		changeState(new AttackState());
		return;
	}

	m_slackTimer += (float)dt;
	if (m_slackTimer >= S_REST_MAX_TIME)
	{
		if (m_currentState == SLACK_REST)
		{
			g->GetView()->SetScale(Vector2(g->GetDefaultViewRadius() * 2.f, g->GetDefaultViewRadius() * 2.f)); // Set view scale back to default
			g->UpdateViewPosition();
			changeState(new PatrolState());
			return; // Break out of this function
		}
		else if (m_currentState == SLACK_SLEEP)
		{
			g->SetSleep(true);
			changeState(new WakeUpState());
			return; // Break out of this function
		}
	}


}

void SlackState::Exit(void)
{
}
