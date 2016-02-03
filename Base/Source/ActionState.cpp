#include "ActionState.h"

#include "GameCharacter.h"
#include "Enemy.h"
#include "StartTurnState.h"
#include "EnemyStartTurnState.h"

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
		//changeState(new WaitForTurn());
	}
}

void ActionState::Exit(void)
{
}
