#include "EnemySpecialState.h"

#include "Enemy.h"

EnemySpecialState::EnemySpecialState() : FSMState()
{
	m_stateName = "Enemy Special State";
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
	
	Enemy* e = dynamic_cast<Enemy*>(m_FSMOwner);

	// Check if the NPC is legit
	if (!e)
	{
		return;
	}

	// Increment the biding turns
	e->m_currentBideTurns++;

	if (e->m_currentBideTurns >= e->m_bideTurns)
	{
		// We've bided enough

		if (e->GetOpponentTeam().size() > 0) // Someone is in opponent team
		{
			int random = Math::RandIntMinMax(0, e->GetOpponentTeam().size() - 1); // Random an enemy to attack
			e->GetOpponentTeam()[random]->Injure(e->m_attack + e->m_bideStoreDamage);

			// Reset bide status
			e->m_currentBideTurns = 0;
			e->m_bideStoreDamage = 0;
		}
	}

	// End the turn
	e->EndTurn();
}

void EnemySpecialState::Exit(void)
{
}
