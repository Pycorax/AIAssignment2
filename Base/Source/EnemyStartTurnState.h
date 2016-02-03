#ifndef ENEMY_START_TURN_STATE
#define ENEMY_START_TURN_STATE

#include "FSMState.h"

class EnemyStartTurnState : public FSMState
{
public:
	EnemyStartTurnState();
	virtual ~EnemyStartTurnState();

	virtual void Init(NPC* FSMOwner);
	virtual void Init(FSMState* stateOwner);
	virtual void Update(double dt);
	virtual void Exit(void);

private:
};

#endif