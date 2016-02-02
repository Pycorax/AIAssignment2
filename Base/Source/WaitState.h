#pragma once

#include "FSMState.h"

class WaitState : public FSMState
{
public:
	WaitState(FSMState* waitState);
	~WaitState();

	virtual void Init(NPC* FSMOwner);
	virtual void Init(FSMState* stateOwner);
	virtual void Update(double dt);
	virtual void Exit(void);
};

