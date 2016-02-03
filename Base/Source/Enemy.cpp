#include "Enemy.h"

#include "WaitState.h"

Enemy::Enemy() : Character()
	// Probabilities
	, m_attackProbability(10)
	, m_stunProbability(20)
	, m_specialProbability(70)
	// Stun Duration
	, m_stunAttackDuration(3)
	// Cool Down
	, m_specCoolDown(0)
{
}


Enemy::~Enemy()
{
}

void Enemy::Init(int maxHealth, int attack, Mesh * mesh)
{
	Character::Init(maxHealth, attack, mesh);

	setCurrentState(new WaitState());
}

void Enemy::StartTurn()
{
	Character::StartTurn();
	--m_specCoolDown;
}

bool Enemy::canUseSpecialAttack()
{
	return m_specCoolDown <= 0;
}

int Enemy::getStunAttackDuration()
{
	return m_stunAttackDuration;
}
