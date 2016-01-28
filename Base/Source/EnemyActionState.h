#ifndef ENEMY_ACTION_STATE
#define ENEMY_ACTION_STATE

#include "FSMState.h"

class EnemyActionState : public FSMState
{	
public:
	EnemyActionState();
	~EnemyActionState();

	// Initialization function for Base NPC States
	virtual void Init(NPC* FSMOwner);
	// Initialization function for Nested States
	virtual void Update(double dt);
};

#endif