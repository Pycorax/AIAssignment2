#include "BombState.h"

#include "SpyNPC.h"
#include "RespawnState.h"

BombState::BombState() : FSMState()
{
	m_stateName = "BombState";
}


BombState::~BombState()
{
}

void BombState::Update(double dt)
{
	SpyNPC* spy = dynamic_cast<SpyNPC*>(m_FSMOwner);

	if (spy)
	{
		spy->m_combatRecord++;
	}

	changeState(new RespawnState);
}