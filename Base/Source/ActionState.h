#ifndef _ACTION_STATE_H_
#define _ACTION_STATE_H_

#include "FSMState.h"
#include "GameCharacter.h"

class ActionState : public FSMState
{
public:
	ActionState();
	virtual ~ActionState();

	virtual void Init(NPC* FSMOwner);
	virtual void Init(FSMState* stateOwner);
	virtual void Update(double dt);
	virtual void Exit(void);

private:
};

#endif