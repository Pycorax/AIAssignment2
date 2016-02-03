#include "EnemyStartTurnState.h"

// State change
#include "AttackState.h"
#include "DefendState.h"
#include "PassState.h"
#include "Enemy.h"
#include "StunAttackState.h"
#include "EnemySpecialState.h"

EnemyStartTurnState::EnemyStartTurnState() : FSMState()
{
	m_stateName = "Enemy Start Turn State";
}


EnemyStartTurnState::~EnemyStartTurnState()
{
}

void EnemyStartTurnState::Init(NPC * FSMOwner)
{
	FSMState::Init(FSMOwner);
}

void EnemyStartTurnState::Init(FSMState * stateOwner)
{
	// Attach the handle to the state owner
	FSMState::Init(stateOwner);
}

void EnemyStartTurnState::Update(double dt)
{
	FSMState::Update(dt);

	// Get the actual NPC-type pointer
	Enemy* c = dynamic_cast<Enemy*>(m_FSMOwner);

	// Check if the NPC is legit
	if (!c)
	{
		return;
	}

	// If we are biding, continue biding instead of choosing another move
	if (c->m_bideTurns > 0)
	{
		changeState(new EnemySpecialState());
	}
	else
	{
		// Probabilities
		short attProb = c->m_attackProbability;
		short stunProb = c->m_stunProbability;
		short specProb = c->m_specialProbability;

		// Random
		short maxRand = attProb + stunProb + specProb;
		short random = Math::RandIntMinMax(0, maxRand);

		// Find out which action is chosen
		if (random <= stunProb)
		{
			changeState(new StunAttackState());
		}
		else
		{
			if (random <= specProb && c->canUseSpecialAttack())
			{
				changeState(new EnemySpecialState());
			}
			else
			{
				changeState(new AttackState());
			}
		}
	}
}

void EnemyStartTurnState::Exit(void)
{
}
