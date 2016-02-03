#pragma once

#include "FSMState.h"

class WaitState : public FSMState
{
public:
	enum WAIT_TYPE
	{
		WT_NORMAL,
		WT_VULN,
		WT_DEFEND,
		WT_BIDE
	};

	WaitState();
	~WaitState();

	virtual void Init(NPC* FSMOwner);
	virtual void Init(FSMState* stateOwner);
	virtual void Update(double dt);
	virtual void Exit(void);
};

