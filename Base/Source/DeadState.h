#ifndef DEAD_STATE_H
#define DEAD_STATE_H

#include "FSMState.h"
#include "GameCharacter.h"

class DeadState : public FSMState
{
public:
	DeadState();
	virtual ~DeadState();

	virtual void Init(NPC* FSMOwner);
	virtual void Init(FSMState* stateOwner);
	virtual void Update(double dt);
	virtual void Exit(void);

private:
	void sharedInit(void);
};

#endif