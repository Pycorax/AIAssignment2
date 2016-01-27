#ifndef MOVE_TARGET_STATE_H
#define MOVE_TARGET_STATE_H

#include "FSMState.h"

class MoveTargetState : public FSMState
{
public:
	MoveTargetState();
	~MoveTargetState();

	void Update(double dt);
};

#endif