#ifndef HUNTING_ENEMY_STATE_H
#define HUNTING_ENEMY_STATE_H

#include "FSMState.h"

class HuntingEnemyState : public FSMState
{
public:
	HuntingEnemyState();
	~HuntingEnemyState();

	void Init(NPC* FSMOwner);
	void Update(double dt);
	void Exit(void);


};

#endif