#include "WaitState.h"

#include "GameCharacter.h"
#include "ActionState.h"

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

	// Check if the NPC is legit
	if (!c)
	{
		return;
	}

	// It is our turn? Let's go
	if (!c->GetEndTurn())
	{
		// Determine whether this is an enemy or a normal character
		GameCharacter* gc = dynamic_cast<GameCharacter*>(m_FSMOwner);

		if (gc)
		{
			changeState(new ActionState());
		}
	}
}

void WaitState::Exit(void)
{
}

