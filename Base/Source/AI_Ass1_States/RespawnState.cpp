#include "RespawnState.h"

#include "ToTargetState.h"

#include "Vector2.h"
#include "SpyNPC.h"

RespawnState::RespawnState()
{
	m_stateName = "RespawnState";
}


RespawnState::~RespawnState()
{
}

void RespawnState::Init(void)
{
	// Reset all Variables
	SpyNPC* spy = dynamic_cast<SpyNPC*>(m_FSMOwner);
	if (spy)
	{
		spy->m_prevWaypoint = NULL;
		spy->m_guardTarget = NULL;
		spy->m_onRoad = false;
		spy->m_isTargeted = false;
	}
}

void RespawnState::Update(double dt)
{
	respawnRandomly();
	changeState(new ToTargetState);
}

void RespawnState::respawnRandomly(void)
{
	static const size_t NUM_SPAWN_SPOTS = 5;
	static const Vector2 MIN_SPAWN(100.0f, 550.0f);
	static const Vector2 MAX_SPAWN(1100.0f, 620.0f);

	SpyNPC* spy = dynamic_cast<SpyNPC*>(m_FSMOwner);
	if (spy)
	{
		// Randomly select a spawn
		spy->m_transforms.Translation = Vector2(Math::RandFloatMinMax(MIN_SPAWN.x, MAX_SPAWN.x), Math::RandFloatMinMax(MIN_SPAWN.y, MAX_SPAWN.y));
		spy->GoToNearestWaypoint();
	}
}
