#ifndef _ATTACK_STATE_H_
#define _ATTACK_STATE_H_

#include "FSMState.h"
#include "GameCharacter.h"

class AttackState : public FSMState
{
public:
	AttackState();
	virtual ~AttackState();

	virtual void Init(NPC* FSMOwner);
	virtual void Init(FSMState* stateOwner);
	virtual void Update(double dt);
	virtual void Exit(void);

private:
};

#endif