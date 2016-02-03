#include "ActionState.h"

#include "GameCharacter.h"
#include "Enemy.h"

// State includes
#include "StartTurnState.h"
#include "EnemyStartTurnState.h"
#include "StunnedState.h"

ActionState::ActionState() : FSMState()
{
	m_stateName = "Action State";
}


ActionState::~ActionState()
{
}

void ActionState::Init(NPC * FSMOwner)
{
	FSMState::Init(FSMOwner);

	// Get the actual Character-type pointer
	GameCharacter* c = dynamic_cast<GameCharacter*>(m_FSMOwner);
	Enemy* e = dynamic_cast<Enemy*>(m_FSMOwner);

	// Check if the NPC is legit
	if (c)
	{
		setCurrentState(new StartTurnState());
	}
	else if (e)
	{
		setCurrentState(new EnemyStartTurnState());
	}
}

void ActionState::Init(FSMState * stateOwner)
{
	// Get the actual Character-type pointer
	GameCharacter* c = dynamic_cast<GameCharacter*>(m_FSMOwner);

	// Check if the NPC is legit
	if (!c)
	{
		return;
	}

	// Attach the handle to the state owner
	FSMState::Init(stateOwner);
}

void ActionState::Update(double dt)
{

	// Get the actual Character-type pointer
	GameCharacter* c = dynamic_cast<GameCharacter*>(m_FSMOwner);
	Enemy* e = dynamic_cast<Enemy*>(m_FSMOwner);

	/*if ((c && c->GetEndTurn()) || (e && e->GetEndTurn()))
	{
		return;
	}*/

	FSMState::Update(dt);

	if (c)
	{
		if (c->IsStunned())
		{
			changeState(new StunnedState());
		}
		else if (c->GetEndTurn())
		{
			changeState(new WaitState());
		}
	}
	else if (e)
	{
		if (e->IsStunned())
		{
			// Stun state if get stunned
			changeState(new StunnedState());
		}
		else if (e->GetEndTurn())
		{
			// End turn once action ended
			changeState(new WaitState());
		}
	}
	else
	{
		// Both NPC does not exist
		return;
	}
}

void ActionState::Exit(void)
{
}
