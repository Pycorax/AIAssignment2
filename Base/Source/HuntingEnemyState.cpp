#include "HuntingEnemyState.h"

#include "RunEnemyState.h"
#include "ToTargetState.h"
#include "BombState.h"
#include "MyMath.h"
#include "SpyNPC.h"

HuntingEnemyState::HuntingEnemyState() : FSMState()
{
	m_stateName = "HuntingEnemyState";
}


HuntingEnemyState::~HuntingEnemyState()
{
}

void HuntingEnemyState::Init(NPC * FSMOwner)
{
	FSMState::Init(FSMOwner);
	
	// Get a handle to the spy
	SpyNPC* spy = dynamic_cast<SpyNPC*>(m_FSMOwner);

	if (spy)
	{
		// Set up the child state
		setCurrentState(new RunEnemyState);
	}
}

void HuntingEnemyState::Update(double dt)
{
	// Run the child state
	FSMState::Update(dt);

	// Get a handle to the spy
	SpyNPC* spy = dynamic_cast<SpyNPC*>(m_FSMOwner);

	if (spy)
	{
		// Trigger Conditions here
		// -- If the guard is rekt, no point trying to attack it anymore
		if (spy->m_guardTarget->GetKnockedOut())
		{
			changeState(new ToTargetState);
		}

		if (spy->ReachedTarget())
		{
			changeState(new BombState);
		}
	}
}

void HuntingEnemyState::Exit(void)
{
	FSMState::Exit();
}
