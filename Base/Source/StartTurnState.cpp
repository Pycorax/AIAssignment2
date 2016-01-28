#include "StartTurnState.h"

// State change
#include "AttackState.h"
#include "DefendState.h"
#include "PassState.h"

StartTurnState::StartTurnState() : FSMState()
{
}


StartTurnState::~StartTurnState()
{
}

void StartTurnState::Init(NPC * FSMOwner)
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

void StartTurnState::Init(FSMState * stateOwner)
{
	// Attach the handle to the state owner
	FSMState::Init(stateOwner);

	// Get the actual NPC-type pointer
	GameCharacter* c = dynamic_cast<GameCharacter*>(m_FSMOwner);

	// Check if the NPC is legit
	if (!c)
	{
		return;
	}
}

void StartTurnState::Update(double dt)
{
	FSMState::Update(dt);

	// Get the actual NPC-type pointer
	GameCharacter* c = dynamic_cast<GameCharacter*>(m_FSMOwner);

	// Check if the NPC is legit
	if (!c)
	{
		return;
	}

	// Probabilities
	short attProb = c->GetAttackProbability();
	short defProb = c->GetDefendProbability();
	short specProb = c->GetSpecialProbability();
	short passProb = c->GetPassProbability();

	// Random
	short maxRand = attProb + defProb + specProb + passProb;
	short random = Math::RandIntMinMax(1, maxRand);

	// Find out which action is chosen
	if (random <= attProb)
	{
		std::cout << "Attack" << std::endl;
		changeState(new AttackState());
	}
	else if (random > attProb && random <= attProb + defProb)
	{
		std::cout << "Defend" << std::endl;
		changeState(new DefendState());
	}
	else if (random > attProb + defProb && random <= attProb + defProb + specProb)
	{
		std::cout << "Special" << std::endl;
		// TODO: Set to special state
	}
	else
	{
		std::cout << "Pass" << std::endl;
		changeState(new PassState());
	}
}

void StartTurnState::Exit(void)
{
}
