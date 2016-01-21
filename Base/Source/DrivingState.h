#ifndef DRIVING_STATE_H
#define DRIVING_STATE_H

// Inheritance Includes
#include "FSMState.h"

class DrivingState : public FSMState
{
public:
	DrivingState();
	~DrivingState();

	void Update(double dt);
};

#endif