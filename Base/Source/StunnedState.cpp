#include "StunnedState.h"

StunnedState::StunnedState() : FSMState()
{
	m_stateName = "Stunned state";
}


StunnedState::~StunnedState()
{
}

void StunnedState::Init(NPC * FSMOwner)
{
	FSMState::Init(FSMOwner);

	// Get the actual NPC-type pointer
	GameCharacter* c = dynamic_cast<GameCharacter*>(m_FSMOwner);

	// Check if the NPC is legit
	if (!c)
	{
		return;
	}

	// Set up the child state
}

void StunnedState::Init(FSMState * stateOwner)
{
	// Attach the handle to the state owner
	FSMState::Init(stateOwner);

	// Get the actual NPC-type pointer
	GameCharacter* c = dynamic_cast<GameCharacter*>(m_FSMOwner);

	// Check if the NPC is legit
	if (!c)
	{
		return;
	}
}

void StunnedState::Update(double dt)
{
	FSMState::Update(dt);

	// Get the actual NPC-type pointer
	GameCharacter* c = dynamic_cast<GameCharacter*>(m_FSMOwner);

	// Check if the NPC is legit
	if (!c)
	{
		return;
	}
}

void StunnedState::Exit(void)
{
}
