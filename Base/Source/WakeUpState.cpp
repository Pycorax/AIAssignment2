#include "WakeUpState.h"
#include "RetreatState.h"

const float WakeUpState::S_TIME_TO_CONSCIOUS = 2.f;

WakeUpState::WakeUpState() : FSMState(), m_WakeUpTimer(0.f), m_scalingSpeed(0.f)
{
	m_stateName = "Wake up State";
}


WakeUpState::~WakeUpState()
{
}

void WakeUpState::Init(NPC * FSMOwner)
{
	FSMState::Init(FSMOwner);
	m_WakeUpTimer = 0.f;

	Guard* g = dynamic_cast<Guard*>(m_FSMOwner);

	// Check if the NPC is legit
	if (!g)
	{
		return;
	}

	float scalingSpeed = (g->GetDefaultViewRadius() * 2.f) / S_TIME_TO_CONSCIOUS;
	m_scalingSpeed.Set(scalingSpeed, scalingSpeed, scalingSpeed);

	if (!g->GetSleep())
	{
		g->SetRegainConscious(true);
	}

	// Set up the child state
}

void WakeUpState::Init(FSMState * stateOwner)
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

	float scalingSpeed = (g->GetDefaultViewRadius() * 2.f) / S_TIME_TO_CONSCIOUS;
	m_scalingSpeed.Set(scalingSpeed, scalingSpeed, scalingSpeed);

	if (!g->GetSleep())
	{
		g->SetRegainConscious(true);
	}
}

void WakeUpState::Update(double dt)
{
	FSMState::Update(dt);
	Guard* g = dynamic_cast<Guard*>(m_FSMOwner);
	if (!g)
	{
		return;
	}

	if (g->GetAttacked() && g->GetKnockedOut())
	{
		changeState(new KnockOutState());
		return;
	}

	m_WakeUpTimer += (float)dt;
	if (m_WakeUpTimer >= S_TIME_TO_CONSCIOUS)
	{
		g->GetView()->SetScale(Vector2(g->GetDefaultViewRadius() * 2.f, g->GetDefaultViewRadius() * 2.f));
		g->UpdateViewPosition();
		if (g->GetSleep())
		{
			g->SetSleep(false);
			changeState(new PatrolState());
		}
		else
		{
			g->SetRegainConscious(false);
			changeState(new RetreatState(g->GetTransform().Translation));
		}
		return; // Break out of this function
	}
	else
	{
		Vector3 viewScale = g->GetView()->GetTransform().Scale;
		g->GetView()->SetScale(viewScale + m_scalingSpeed * dt);
		g->UpdateViewPosition();
	}
}

void WakeUpState::Exit(void)
{
}
