#include "WaitState.h"

#include "GameCharacter.h"
#include "Enemy.h"

// States include
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
	Enemy* e = dynamic_cast<Enemy*>(m_FSMOwner);

	// It is our turn? Let's go
	if (c)
	{
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
	else if (e)
	{
		if (!e->GetEndTurn())
		{
			// Determine whether this is an enemy or a normal character
			GameCharacter* gc = dynamic_cast<GameCharacter*>(m_FSMOwner);

			if (gc)
			{
				changeState(new ActionState());
			}
		}
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

