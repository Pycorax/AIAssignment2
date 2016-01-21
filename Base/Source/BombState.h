#ifndef BOMB_STATE_H
#define BOMB_STATE_H

#include "FSMState.h"

class BombState : public FSMState
{
public:
	BombState();
	~BombState();

	void Update(double dt);
};

#endif