#ifndef ENEMY_SPECIAL_STATE_H
#define ENEMY_SPECIAL_STATE_H

#include "FSMState.h"
#include "GameCharacter.h"

class EnemySpecialState : public FSMState
{
public:
	EnemySpecialState();
	virtual ~EnemySpecialState();

	virtual void Init(NPC* FSMOwner);
	virtual void Init(FSMState* stateOwner);
	virtual void Update(double dt);
	virtual void Exit(void);
};

#endif