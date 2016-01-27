#ifndef _DEFEND_STATE_H_
#define _DEFEND_STATE_H_

#include "FSMState.h"
#include "GameCharacter.h"

class DefendState : public FSMState
{
public:
	DefendState();
	virtual ~DefendState();

	virtual void Init(NPC* FSMOwner);
	virtual void Init(FSMState* stateOwner);
	virtual void Update(double dt);
	virtual void Exit(void);

private:
};

#endif