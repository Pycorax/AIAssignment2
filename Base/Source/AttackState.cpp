#include "AttackState.h"

AttackState::AttackState() : FSMState()
{
	m_stateName = "Attack State";
}


AttackState::~AttackState()
{
}

void AttackState::Init(NPC * FSMOwner)
{
	FSMState::Init(FSMOwner);

	// Get the actual Character-type pointer
	GameCharacter* c = dynamic_cast<GameCharacter*>(m_FSMOwner);

	// Check if the NPC is legit
	if (!c)
	{
		return;
	}

	// Set up the child state
}

void AttackState::Init(FSMState * stateOwner)
{
	// Attach the handle to the state owner
	FSMState::Init(stateOwner);

	// Get the actual Character-type pointer
	GameCharacter* c = dynamic_cast<GameCharacter*>(m_FSMOwner);

	// Check if the NPC is legit
	if (!c)
	{
		return;
	}
}

void AttackState::Update(double dt)
{
	// Pause state update for a duration
	if (m_stateTimer < S_MAX_STATE_TIME)
	{
		m_stateTimer += dt;
		return;
	}
	else
	{
		m_stateTimer = 0.f;
	}

	FSMState::Update(dt);

	// Get the actual Character-type pointer
	GameCharacter* c = dynamic_cast<GameCharacter*>(m_FSMOwner);

	// Check if the NPC is legit
	if (!c)
	{
		return;
	}

	if (c->GetOpponentTeam().size() > 0) // Someone is in opponent team
	{
		int random = Math::RandIntMinMax(0, c->GetOpponentTeam().size() - 1); // Random an enemy to attack
		c->GetOpponentTeam()[random]->Injure(c->GetAttack());
	}

	c->EndTurn(); // After attacking, end the character's turn
}

void AttackState::Exit(void)
{
}
