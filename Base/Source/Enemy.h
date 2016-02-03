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
	friend class EnemyActionState;
	friend class EnemyAttackActionState;
	friend class StunAttackState;

protected:
	// State probability (Out of 100)
	short m_attackProbability;
	short m_stunProbability;
	short m_specialProbability;

	// Power of Attacks
	int m_stunAttackDuration;

	// Special Attack Cooldown
	int m_specCoolDown;

public:
	Enemy();
	~Enemy();

	virtual void StartTurn();

protected:
	bool canUseSpecialAttack();
	int getStunAttackDuration();
};

#endif