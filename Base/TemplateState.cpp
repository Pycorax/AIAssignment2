#include "SlackState.h"

AttackedState::AttackedState() : FSMState()
{
}


AttackedState::~AttackedState()
{
}

void AttackedState::Init(NPC * FSMOwner)
{
	FSMState::Init(FSMOwner);

	// Set up the child state
}

void AttackedState::Init(FSMState * stateOwner)
{
	// Attach the handle to the state owner
	FSMState::Init(stateOwner);

	// Get the actual NPC-type pointer
	Guard* npc = dynamic_cast<Guard*>(m_FSMOwner);

	// Check if the NPC is legit
	if (!npc)
	{
		return;
	}
}

void AttackedState::Update(double dt)
{
	FSMState::Update(dt);
}

void AttackedState::Exit(void)
{
}
