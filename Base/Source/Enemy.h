#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "Character.h"

class Enemy : public Character
{
	/*
	*		State Classes Friend Declarations
	* States should be able to access this class's properties
	*/
	friend class EnemyStartTurnState;
	friend class EnemySpecialState;
	friend class StunAttackState;
	friend class WaitState;

protected:
	// State probability (Out of 100)
	short m_attackProbability;
	short m_stunProbability;
	short m_specialProbability;

	// Power of Attacks
	int m_stunAttackDuration;
	int m_bideStoreDamage;
	int m_bideTurns;
	int m_currentBideTurns;

	// Special Attack Cooldown
	int m_specCoolDown;

public:
	Enemy();
	~Enemy();

	virtual void Init(int maxHealth, int attack, Mesh* mesh);

	virtual void StartTurn();

	virtual void Injure(int damage);

protected:
	bool canUseSpecialAttack();
	int getStunAttackDuration();
};

#endif