#include "StunnedState.h"
#include "GameCharacter.h"
#include "Enemy.h"

// State includes
#include "ActionState.h"

StunnedState::StunnedState() : FSMState()
{
	m_stateName = "Stunned State";
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
	Enemy* e = dynamic_cast<Enemy*>(m_FSMOwner);

	if (c)
	{
		if (!c->IsStunned())
		{
			if (c->GetEndTurn())
			{
				changeState(new WaitState());
			}
			else
			{
				changeState(new ActionState());
			}
		}
	}
	else if (e)
	{
		if (!e->IsStunned())
		{
			if (e->GetEndTurn())
			{
				changeState(new WaitState());
			}
			else
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

void StunnedState::Update(double dt)
{
	FSMState::Update(dt);

	// Get the actual NPC-type pointer
	GameCharacter* c = dynamic_cast<GameCharacter*>(m_FSMOwner);
	Enemy* e = dynamic_cast<Enemy*>(m_FSMOwner);

	// Check if the NPC is legit
	if (!c)
	{
		return;
	}
}

void StunnedState::Exit(void)
{
}
