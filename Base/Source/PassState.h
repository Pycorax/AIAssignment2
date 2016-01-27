#ifndef _PASS_STATE_H_
#define _PASS_STATE_H_

#include "FSMState.h"
#include "GameCharacter.h"

class PassState : public FSMState
{
public:
	PassState();
	virtual ~PassState();

	virtual void Init(NPC* FSMOwner);
	virtual void Init(FSMState* stateOwner);
	virtual void Update(double dt);
	virtual void Exit(void);

private:
};

#endif