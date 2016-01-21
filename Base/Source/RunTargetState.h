#ifndef RUN_TARGET_STATE_H
#define RUN_TARGET_STATE_H

#include "MoveTargetState.h"

class RunTargetState : public MoveTargetState
{

	static const float NEAR_DIST_TO_TARGET_SQUARED;
	static const int CHANCE_WALK_WHEN_NEAR = 90;

public:
	RunTargetState();
	~RunTargetState();

	void Init(NPC* FSMOwner);
	void Init(FSMState* stateParent);
	void Update(double dt);
};

#endif