#ifndef _ATTACKEDSTATE_H_
#define _ATTACKEDSTATE_H_

#include "FSMState.h"
#include "GameCharacter.h"

class StunnedState : public FSMState
{
public:
	StunnedState();
	virtual ~StunnedState();

	virtual void Init(NPC* FSMOwner);
	virtual void Init(FSMState* stateOwner);
	virtual void Update(double dt);
	virtual void Exit(void);

private:
};

#endif