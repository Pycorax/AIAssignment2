#include "KnockOutState.h"

const float KnockOutState::S_TIME_TO_WAKE_UP = 3.f;

KnockOutState::KnockOutState() : FSMState(), m_KnockedOutTimer(0.f)
{
	m_stateName = "Knockout State";
}


KnockOutState::~KnockOutState()
{
}

void KnockOutState::Init(NPC * FSMOwner)
{
	FSMState::Init(FSMOwner);
	m_KnockedOutTimer = 0.f;

	Guard* g = dynamic_cast<Guard*>(m_FSMOwner);

	// Check if the NPC is legit
	if (!g)
	{
		return;
	}

	// Set up the child state
}

void KnockOutState::Init(FSMState * stateOwner)
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

	g->GetView()->SetScale(Vector3::ZERO_VECTOR);
	g->GetView()->SetActive(false);
	g->SetAttacker(nullptr);
	g->SetTarget(nullptr);
}

void KnockOutState::Update(double dt)
{
	FSMState::Update(dt);
	Guard* g = dynamic_cast<Guard*>(m_FSMOwner);
	if (!g)
	{
		return;
	}

	m_KnockedOutTimer += (float)dt;
	if (m_KnockedOutTimer >= S_TIME_TO_WAKE_UP)
	{
		g->GetView()->SetActive(true);
		g->SetKnockedOut(false);
		changeState(new WakeUpState());
		return; // Break out of this function
	}
}

void KnockOutState::Exit(void)
{
}
