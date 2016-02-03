#include "EnemySpecialState.h"

EnemySpecialState::EnemySpecialState() : FSMState()
{
}


EnemySpecialState::~EnemySpecialState()
{
}

void EnemySpecialState::Init(NPC * FSMOwner)
{
	FSMState::Init(FSMOwner);

	// Set up the child state
}

void EnemySpecialState::Init(FSMState * stateOwner)
{
	// Attach the handle to the state owner
	FSMState::Init(stateOwner);
}

void EnemySpecialState::Update(double dt)
{
	FSMState::Update(dt);

	// Get the actual NPC-type pointer
	GameCharacter* c = dynamic_cast<GameCharacter*>(m_FSMOwner);

	// Check if the NPC is legit
	if (!c)
	{
		return;
	}

	// Determine which character
}

void EnemySpecialState::Exit(void)
{
}
