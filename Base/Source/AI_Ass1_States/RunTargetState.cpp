#include "RunTargetState.h"

#include "SpyNPC.h"
#include "SneakTargetState.h"

const float RunTargetState::NEAR_DIST_TO_TARGET_SQUARED = 200.0f * 200.0f;

RunTargetState::RunTargetState()
{
	m_stateName = "RunTargetState";
}


RunTargetState::~RunTargetState()
{
}

void RunTargetState::Init(NPC * FSMOwner)
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

	// Set the movement mode to sprinting
	npc->m_moveMode = SpyNPC::MM_SPRINT;
}

void RunTargetState::Init(FSMState* stateParent)
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

	// Set the movement mode to sprinting
	npc->m_moveMode = SpyNPC::MM_SPRINT;
}

void RunTargetState::Update(double dt)
{
	MoveTargetState::Update(dt);

	// Get the actual NPC-type pointer
	SpyNPC* spy = dynamic_cast<SpyNPC*>(m_FSMOwner);

	if (spy
		&&
		spy->GetDistSqrToBombTarget() <= NEAR_DIST_TO_TARGET_SQUARED
		&&
		Math::GetChance(CHANCE_WALK_WHEN_NEAR)
		)
	{
		changeState(new SneakTargetState);
	}
}
