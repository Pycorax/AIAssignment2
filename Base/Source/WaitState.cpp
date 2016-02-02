#include "WaitState.h"


WaitState::WaitState(FSMState* waitState)
{
	// Set up the child state
	setCurrentState(waitState);
}


WaitState::~WaitState()
{
}

void WaitState::Init(NPC * FSMOwner)
{
	FSMState::Init(FSMOwner);	
}

void WaitState::Init(FSMState * stateOwner)
{
	// Attach the handle to the state owner
	FSMState::Init(stateOwner);
}

void WaitState::Update(double dt)
{

	// Get the actual Character-type pointer
	GameCharacter* c = dynamic_cast<GameCharacter*>(m_FSMOwner);

	// Check if the NPC is legit
	if (!c)
	{
		return;
	}

	if (c->GetEndTurn())
	{
		return;
	}

	FSMState::Update(dt);

	// End turn once action is over
	if (c->GetEndTurn())
	{
		
	}
}

void WaitState::Exit(void)
{
}

