#include "StartTurnState.h"

// State change
#include "AttackState.h"
#include "DefendState.h"
#include "PassState.h"
#include "SpecialState.h"

StartTurnState::StartTurnState() : FSMState()
{
	m_stateName = "Start Turn State";
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
	// Pause state update for a duration
	if (m_stateTimer < S_MAX_STATE_TIME)
	{
		m_stateTimer += dt;
		return;
	}
	else
	{
		m_stateTimer = 0.f;
	}

	FSMState::Update(dt);

	// Get the actual NPC-type pointer
	GameCharacter* c = dynamic_cast<GameCharacter*>(m_FSMOwner);

	// Check if the NPC is legit
	if (!c)
	{
		return;
	}

	// Special conditions that leads to instant choice of special
	Character* target = c->GetNextTarget();
	if (target)
	{
		if (c->GetType() == GameCharacter::GC_HEALER || c->GetType() == GameCharacter::GC_TANK)
		{
			changeState(new SpecialState(target));
			return;
		}
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
		//std::cout << "Attack" << std::endl;
		changeState(new AttackState());
	}
	else if (random > attProb && random <= attProb + defProb)
	{
		//std::cout << "Defend" << std::endl;
		changeState(new DefendState());
	}
	else if (random > attProb + defProb && random <= attProb + defProb + specProb)
	{
		// TODO: Set to special state
		switch (c->GetType())
		{
		case GameCharacter::GC_HEALER:
			{
			}
			break;
		case GameCharacter::GC_RANGER:
			{
				int random = Math::RandIntMinMax(0, c->GetOpponentTeam().size() - 1); // Random an enemy to attack
				target = c->GetOpponentTeam()[random];
			}
			break;
		case GameCharacter::GC_TANK:
			{
			}
			break;
		case GameCharacter::GC_WARRIOR:
			{
			}
			break;
		}
		changeState(new SpecialState(target));
	}
	else
	{
		//std::cout << "Pass" << std::endl;
		changeState(new PassState());
	}
}

void StartTurnState::Exit(void)
{
}
