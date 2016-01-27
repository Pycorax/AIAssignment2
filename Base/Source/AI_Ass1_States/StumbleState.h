#ifndef STUMBLE_STATE_H
#define STUMBLE_STATE_H

#include "FSMState.h"

class StumbleState : public FSMState
{
	static const float STUMBLE_DURATION;
	static const int CHANCE_TO_RUN_AWAY = 55;
	float stumbledDuration;

public:
	StumbleState();
	~StumbleState();

	void Update(double dt);
};

#endif