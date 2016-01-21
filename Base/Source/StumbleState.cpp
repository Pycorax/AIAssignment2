#include "StumbleState.h"

#include "SpyNPC.h"
#include "RunToSpawnState.h"
#include "RunEnemyState.h"

const float StumbleState::STUMBLE_DURATION = 2.0f;

StumbleState::StumbleState() : FSMState()
	, stumbledDuration(0.0f)
{
	m_stateName = "StumbleState";
}


StumbleState::~StumbleState()
{
}

void StumbleState::Update(double dt)
{
	FSMState::Update(dt);

	stumbledDuration += dt;

	if (stumbledDuration >= STUMBLE_DURATION)
	{
		if (Math::GetChance(CHANCE_TO_RUN_AWAY))
		{
			changeState(new RunToSpawnState);
		}
		else
		{
			changeState(new RunEnemyState);
		}
	}
}