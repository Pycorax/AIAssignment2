#ifndef RUN_TO_SPAWN_STATE_H
#define RUN_TO_SPAWN_STATE_H

#include "FSMState.h"

class RunToSpawnState : public FSMState
{
	bool m_reachedSafeZone;

public:
	RunToSpawnState();
	~RunToSpawnState();

	void Init(NPC* FSMOwner);
	void Init(FSMState* stateParent);
	void Update(double dt);
};

#endif