#include "DeadState.h"

DeadState::DeadState() : FSMState()
{
	m_stateName = "Dead state";
}


DeadState::~DeadState()
{
}

void DeadState::Init(NPC * FSMOwner)
{
	FSMState::Init(FSMOwner);

	sharedInit();
}

void DeadState::Init(FSMState * stateOwner)
{
	// Attach the handle to the state owner
	FSMState::Init(stateOwner);

	sharedInit();
}

void DeadState::Update(double dt)
{
	FSMState::Update(dt);
}

void DeadState::Exit(void)
{
}

void DeadState::sharedInit(void)
{
	// Get the actual Character-type pointer
	GameCharacter* c = dynamic_cast<GameCharacter*>(m_FSMOwner);

	// Check if the NPC is legit
	if (!c)
	{
		return;
	}

	// Send the death message
	c->sendMessage(Message::MSG_DEATH);
	// -- Decide if we are going to be a matyr or cry
	if (Math::RandIntMinMax(0, 1))
	{
		c->sendMessage(Message::MSG_LAST_WORDS);
	}
	else
	{
		c->sendMessage(Message::MSG_MARTYRDOM);
	}
}
