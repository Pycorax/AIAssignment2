#ifndef STUN_ATTACK_STATE_H
#define STUN_ATTACK_STATE_H

#include "FSMState.h"
#include "GameCharacter.h"

class StunAttackState : public FSMState
{
public:
	StunAttackState();
	virtual ~StunAttackState();

	virtual void Init(NPC* FSMOwner);
	virtual void Init(FSMState* stateOwner);
	virtual void Update(double dt);
	virtual void Exit(void);

private:
};

#endif