#ifndef RUN_ENEMY_STATE_H
#define RUN_ENEMY_STATE_H

#include "FSMState.h"

class RunEnemyState : public FSMState
{
	static const float NEAR_DIST_TO_TARGET_SQUARED;
	static const short CHANCE_SUCCESS_ATTACK = 80;

public:
	RunEnemyState();
	~RunEnemyState();

	void Init(NPC* FSMOwner);
	void Init(FSMState* stateParent);
	void Update(double dt);
};

#endif