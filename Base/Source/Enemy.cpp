#include "Enemy.h"

#include "WaitState.h"

Enemy::Enemy() : Character()
	// Probabilities
	, m_attackProbability(10)
	, m_stunProbability(20)
	, m_specialProbability(70)
	// Attack Power
	, m_stunAttackDuration(3)
	, m_bideStoreDamage(0)
	, m_bideTurns(2)
	, m_currentBideTurns(0)
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

void Enemy::Injure(int damage)
{
	static const float VULN_MULTIPLIER = 2.0f;

	switch (m_waitType)
	{
		case WaitState::WT_VULN:
			damage *= VULN_MULTIPLIER;
			break;
		case WaitState::WT_BIDE:
			m_bideStoreDamage += damage;
			break;
	}

	Character::Injure(damage);
}

bool Enemy::canUseSpecialAttack()
{
	return m_specCoolDown <= 0;
}

int Enemy::getStunAttackDuration()
{
	return m_stunAttackDuration;
}

void Enemy::handleMessage(Message msg)
{
}
