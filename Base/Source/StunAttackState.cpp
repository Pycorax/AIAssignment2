#include "StunAttackState.h"
#include "Enemy.h"

StunAttackState::StunAttackState() : FSMState()
{
	m_stateName = "Stun Attack State";
}


StunAttackState::~StunAttackState()
{
}

void StunAttackState::Init(NPC * FSMOwner)
{
	FSMState::Init(FSMOwner);
}

void StunAttackState::Init(FSMState * stateOwner)
{
	// Attach the handle to the state owner
	FSMState::Init(stateOwner);
}

void StunAttackState::Update(double dt)
{
	FSMState::Update(dt);

	// Get the actual Character-type pointer
	Enemy* c = dynamic_cast<Enemy*>(m_FSMOwner);

	// Check if the NPC is legit
	if (!c)
	{
		return;
	}

	if (c->GetOpponentTeam().size() > 0) // Someone is in opponent team
	{
		int random = Math::RandIntMinMax(0, c->GetOpponentTeam().size() - 1); // Random an enemy to attack
		c->GetOpponentTeam()[random]->Stun(c->getStunAttackDuration());
	}

	c->EndTurn(); // After attacking, end the character's turn
}

void StunAttackState::Exit(void)
{
}
