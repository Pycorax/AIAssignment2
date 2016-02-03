#include "WaitState.h"

#include "GameCharacter.h"
#include "Enemy.h"

// States include
#include "ActionState.h"
#include "DeadState.h"
#include "StunnedState.h"

WaitState::WaitState()
{
	m_stateName = "Wait state";
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
	FSMState::Update(dt);

	// Get the actual Character-type pointer
	Character* c = dynamic_cast<Character*>(m_FSMOwner);

	// Invalid pointer
	if (!c)
	{
		return;
	}

	// It is our turn? Let's go
	if (!c->IsAlive())
	{
		// Go to dead state
		changeState(new DeadState());

	}
	else if (c->GetStunnedTurns() > 0)
	{
		changeState(new StunnedState());
	}
	else if (!c->GetEndTurn())
	{
		changeState(new ActionState());
	}
	else
	{
		// Both NPC does not exist
		return;
	}
}

void WaitState::Exit(void)
{
}

