#include "MoveTargetState.h"

#include "SpyNPC.h"

MoveTargetState::MoveTargetState()
{
	m_stateName = "MoveTargetState";
}


MoveTargetState::~MoveTargetState()
{
}

void MoveTargetState::Update(double dt)
{
	// Get the actual NPC-type pointer
	SpyNPC* npc = dynamic_cast<SpyNPC*>(m_FSMOwner);

	// Check if the NPC is legit
	if (!npc)
	{
		return;
	}

	npc->GoToNextWaypoint(dt);
}