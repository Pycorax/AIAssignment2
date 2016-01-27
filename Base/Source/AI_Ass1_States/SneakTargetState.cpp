#include "SneakTargetState.h"

#include "SpyNPC.h"
#include "RunTargetState.h"

SneakTargetState::SneakTargetState()
{
	m_stateName = "SneakTargetState";
}


SneakTargetState::~SneakTargetState()
{
}

void SneakTargetState::Init(NPC * FSMOwner)
{
	// Attach the handle to the state owner
	FSMState::Init(FSMOwner);

	// Get the actual NPC-type pointer
	SpyNPC* npc = dynamic_cast<SpyNPC*>(m_FSMOwner);

	// Check if the NPC is legit
	if (!npc)
	{
		return;
	}

	// Set the movement mode to sneaking
	npc->m_moveMode = SpyNPC::MM_SNEAK;
}

void SneakTargetState::Init(FSMState* stateParent)
{
	// Attach the handle to the state owner
	FSMState::Init(stateParent);

	// Get the actual NPC-type pointer
	SpyNPC* npc = dynamic_cast<SpyNPC*>(m_FSMOwner);

	// Check if the NPC is legit
	if (!npc)
	{
		return;
	}

	// Set the movement mode to sneaking
	npc->m_moveMode = SpyNPC::MM_SNEAK;
}

void SneakTargetState::Update(double dt)
{
	// Do movement
	MoveTargetState::Update(dt);

	// State Triggers
	SpyNPC* npc = dynamic_cast<SpyNPC*>(m_FSMOwner);

	if (npc && npc->m_onRoad)
	{
		changeState(new RunTargetState);
	}
}
