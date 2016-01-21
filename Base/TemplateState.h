#ifndef _ATTACKEDSTATE_H_
#define _ATTACKEDSTATE_H_

#include "FSMState.h"
#include "Guard.h"

class AttackedState : public FSMState
{
public:
	AttackedState();
	virtual ~AttackedState();

	virtual void Init(NPC* FSMOwner);
	virtual void Init(FSMState* stateOwner);
	virtual void Update(double dt);
	virtual void Exit(void);

private:
};

#endif