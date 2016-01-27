#ifndef RESPAWN_STATE_H
#define RESPAWN_STATE_H

#include "FSMState.h"

class RespawnState : public FSMState
{
public:
	RespawnState();
	~RespawnState();

	void Init(void);
	void Update(double dt);

private:
	void respawnRandomly(void);
};
 
#endif