#include "Enemy.h"



Enemy::Enemy()
{
}


Enemy::~Enemy()
{
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
