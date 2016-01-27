#ifndef _START_TURN_STATE_H_
#define _START_TURN_STATE_H_

#include "FSMState.h"
#include "GameCharacter.h"

class StartTurnState : public FSMState
{
public:
	StartTurnState();
	virtual ~StartTurnState();

	virtual void Init(NPC* FSMOwner);
	virtual void Init(FSMState* stateOwner);
	virtual void Update(double dt);
	virtual void Exit(void);

private:
};

#endif