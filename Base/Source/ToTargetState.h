#ifndef TO_TARGET_STATE_H
#define TO_TARGET_STATE_H

#include "FSMState.h"

class ToTargetState : public FSMState
{
	// Attack Guard
	static const float NEAR_DIST_TO_GUARD_SQUARED;
	static const short CHANCE_ATTACK_WHEN_NEAR = 5;
	static const float ATTACK_GUARD_POLL_TIME;
	float m_timeSinceLastPoll;

public:
	ToTargetState();
	~ToTargetState();

	void Init(NPC* FSMOwner);
	void Init(FSMState* state);
	void Update(double dt);
	void Exit(void);
};

#endif