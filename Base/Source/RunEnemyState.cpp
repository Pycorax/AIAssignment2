#include "RunEnemyState.h"

#include "SpyNPC.h"
#include "StumbleState.h"

const float RunEnemyState::NEAR_DIST_TO_TARGET_SQUARED = 50.0f * 50.0f;

RunEnemyState::RunEnemyState()
{
	m_stateName = "RunEnemyState";
}


RunEnemyState::~RunEnemyState()
{
}

void RunEnemyState::Init(NPC * FSMOwner)
{
	// Attach the handle to the state owner
	FSMState::Init(FSMOwner);

	// Get the actual NPC-type pointer
	SpyNPC* spy = dynamic_cast<SpyNPC*>(m_FSMOwner);

	// Check if the NPC is legit
	if (!spy)
	{
		return;
	}

	// Set the movement mode to sprinting
	spy->m_moveMode = SpyNPC::MM_SPRINT;

	// Figure out which is waypoint is nearer to the guard
	float distToEnemyFromLast = (spy->m_prevWaypoint->GetTransform().Translation - spy->GetTransform().Translation).LengthSquared();
	float distToEnemyFromNext = (spy->m_nextWaypoint->GetTransform().Translation - spy->GetTransform().Translation).LengthSquared();

	if (distToEnemyFromLast > distToEnemyFromNext)
	{
		spy->SetNextWaypoint(spy->m_prevWaypoint);
	}
	// else: go to the next waypoint which is already the case
}

void RunEnemyState::Init(FSMState* stateParent)
{
	// Attach the handle to the state owner
	FSMState::Init(stateParent);

	// Get the actual NPC-type pointer
	SpyNPC* npc = dynamic_cast<SpyNPC*>(m_FSMOwner);

	// Check if the NPC is legit
	if (!npc)
	{
		return;
	}

	// Set the movement mode to sprinting
	npc->m_moveMode = SpyNPC::MM_SPRINT;
}

void RunEnemyState::Update(double dt)
{
	// Get the actual NPC-type pointer
	SpyNPC* spy = dynamic_cast<SpyNPC*>(m_FSMOwner);

	// Check if the NPC is legit
	if (!spy)
	{
		return;
	}

	// Arrived
	if (spy->GetDistSqrToGuardTarget() <= NEAR_DIST_TO_TARGET_SQUARED)
	{
		// Notify the enemy of the attack
		spy->m_guardTarget->SetAttacked(true);
		spy->m_guardTarget->SetAttacker(spy);

		if (Math::GetChance(CHANCE_SUCCESS_ATTACK))
		{
			// Knock out the enemy
			spy->m_guardTarget->SetKnockedOut(true);
		}
		else
		{
			// Stumble
			changeState(new StumbleState);
		}
	}
	else
	{
		if (spy->ReachedNextWaypoint())
		{
			// Find the next waypoint to run to, to reach the enemy
			Waypoint* nearestWP = *spy->m_nextWaypoint->GetNext().begin();
			float shortestSqr = ((*spy->m_nextWaypoint->GetNext().begin())->GetTransform().Translation - spy->m_guardTarget->GetTransform().Translation).LengthSquared();
			for (auto w = spy->m_nextWaypoint->GetNext().begin(); w != spy->m_nextWaypoint->GetNext().end(); ++w)
			{
				float thisDistDiff = ((*w)->GetTransform().Translation - spy->m_guardTarget->GetTransform().Translation).LengthSquared();

				if (thisDistDiff < shortestSqr)
				{
					shortestSqr = thisDistDiff;
					nearestWP = (*w);
				}
			}
			spy->SetNextWaypoint(nearestWP);
		}
		else
		{
			// Proceed to target
			Vector2 toTarget = spy->m_nextWaypoint->GetPos() - spy->m_transforms.Translation;
			if (toTarget != Vector2::ZERO_VECTOR)
			{
				// Proceed to the target
				Vector2 dir = toTarget.Normalized();
				spy->m_transforms.Translation += dir * spy->getCurrentSpeed() * dt;
			}
		}
	}
}