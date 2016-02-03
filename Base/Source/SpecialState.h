#ifndef _ATTACKEDSTATE_H_
#define _ATTACKEDSTATE_H_

#include "FSMState.h"
#include "GameCharacter.h"

class SpecialState : public FSMState
{
public:
	SpecialState(Character* target = nullptr);
	virtual ~SpecialState();

	virtual void Init(NPC* FSMOwner);
	virtual void Init(FSMState* stateOwner);
	virtual void Update(double dt);
	virtual void Exit(void);

private:
	Character* m_target;
};

#endif