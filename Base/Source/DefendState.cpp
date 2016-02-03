#include "DefendState.h"

DefendState::DefendState() : FSMState()
{
	m_stateName = "Defend state";
}


DefendState::~DefendState()
{
}

void DefendState::Init(NPC * FSMOwner)
{
	FSMState::Init(FSMOwner);

	// Get the actual Character-type pointer
	GameCharacter* c = dynamic_cast<GameCharacter*>(m_FSMOwner);

	// Check if the NPC is legit
	if (!c)
	{
		return;
	}

	// Set up the child state
}

void DefendState::Init(FSMState * stateOwner)
{
	// Attach the handle to the state owner
	FSMState::Init(stateOwner);

	// Get the actual Character-type pointer
	GameCharacter* c = dynamic_cast<GameCharacter*>(m_FSMOwner);

	// Check if the NPC is legit
	if (!c)
	{
		return;
	}
}

void DefendState::Update(double dt)
{
	FSMState::Update(dt);

	// Get the actual Character-type pointer
	GameCharacter* c = dynamic_cast<GameCharacter*>(m_FSMOwner);

	// Check if the NPC is legit
	if (!c)
	{
		return;
	}

	c->Defend(); // Set character to defensive mode

	c->EndTurn(); // After attacking, end the character's turn
}

void DefendState::Exit(void)
{
}
