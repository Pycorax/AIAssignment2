#ifndef SNEAK_TARGET_STATE_H
#define SNEAK_TARGET_STATE_H

#include "MoveTargetState.h"

class SneakTargetState : public MoveTargetState
{
public:
	SneakTargetState();
	~SneakTargetState();

	void Init(NPC* FSMOwner);
	void Init(FSMState* stateParent);
	void Update(double dt);
};

#endif