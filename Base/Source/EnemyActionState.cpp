#include "EnemyActionState.h"

#include "EnemyAttackActionState.h"

#include "Enemy.h"

EnemyActionState::EnemyActionState()
{
}


EnemyActionState::~EnemyActionState()
{
}

void EnemyActionState::Init(NPC * FSMOwner)
{
	FSMState::Init(FSMOwner);

	Enemy* enemy = dynamic_cast<Enemy*>(m_FSMOwner);

	// Check if the NPC is legit
	if (!enemy)
	{
		return;
	}

	// TODO: Change to the appropriate action's state
}

void EnemyActionState::Update(double dt)
{
	FSMState::Update(dt);

	// Get the actual Character-type pointer
	Enemy* enemy = dynamic_cast<Enemy*>(m_FSMOwner);

	// Check if the NPC is legit
	if (!enemy)
	{
		return;
	}

	// End turn once action is over
	if (enemy->GetEndTurn())
	{
		changeState(new EnemyAttackActionState());
	}
}
