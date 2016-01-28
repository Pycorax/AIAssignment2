#ifndef ENEMY_ATTACK_ACTION_STATE_H
#define ENEMY_ATTACK_ACTION_STATE_H

#include "FSMState.h"

class EnemyAttackActionState : public FSMState
{
public:
	EnemyAttackActionState();
	~EnemyAttackActionState();

	// Initialization function for Nested States
	virtual void Update(double dt);
};

#endif