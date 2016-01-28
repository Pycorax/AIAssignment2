#include "EnemyAttackActionState.h"

#include "Enemy.h"

EnemyAttackActionState::EnemyAttackActionState()
{
}


EnemyAttackActionState::~EnemyAttackActionState()
{
}

void EnemyAttackActionState::Update(double dt)
{
	// Get the actual Character-type pointer
	Enemy* enemy = dynamic_cast<Enemy*>(m_FSMOwner);

	// Check if the NPC is legit
	if (!enemy)
	{
		return;
	}

	// Select an opponent to attack and attack it
	if (enemy->m_opponentTeam.size() > 0)
	{
		int targetID = Math::RandIntMinMax(0, enemy->m_opponentTeam.size());
		enemy->m_opponentTeam.at(targetID)->Injure(enemy->m_attack);
	}
	
	// TODO: Go to end turn state
}
