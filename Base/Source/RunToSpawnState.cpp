#include "RunToSpawnState.h"

#include "SpyNPC.h"
#include "ToTargetState.h"

RunToSpawnState::RunToSpawnState() : FSMState()
	, m_reachedSafeZone(false)
{
	m_stateName = "RunToSpawnState";
}


RunToSpawnState::~RunToSpawnState()
{
}

void RunToSpawnState::Init(NPC * FSMOwner)
{
	// Attach the handle to the state owner
	FSMState::Init(FSMOwner);

	// Get the actual NPC-type pointer
	SpyNPC* npc = dynamic_cast<SpyNPC*>(m_FSMOwner);

	// Check if the NPC is legit
	if (!npc)
	{
		return;
	}

	// Don't go down if we are already safe
	if (npc->GetTransform().Translation.y > 550.0f)		// At the top few waypoints (Hacked together but fast code)
	{
		m_reachedSafeZone = true;

	}

	// Set the movement mode to sprinting
	npc->m_moveMode = SpyNPC::MM_SPRINT;
}

void RunToSpawnState::Init(FSMState* stateParent)
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

	// Don't go down if we are already safe
	if (npc->GetTransform().Translation.y > 550.0f)		// At the top few waypoints (Hacked together but fast code)
	{
		m_reachedSafeZone = true;

	}

	// Set the movement mode to sprinting
	npc->m_moveMode = SpyNPC::MM_SPRINT;
}

void RunToSpawnState::Update(double dt)
{
	// Get the actual NPC-type pointer
	SpyNPC* spy = dynamic_cast<SpyNPC*>(m_FSMOwner);

	// Check if the NPC is legit
	if (!spy)
	{
		return;
	}

	// If we are no longer chased, let's continue
	if (!spy->m_isTargeted)
	{
		spy->m_nextWaypoint = NULL;
		changeState(new ToTargetState);
	}
	else if (m_reachedSafeZone)
	{
		if (spy->GetTransform().Translation.y < 650.0f)
		{
			// Proceed to the top of the map
			spy->m_transforms.Translation += Vector2(0.0f, 1.0f) * spy->getCurrentSpeed() * dt;
		}
	}
	else
	{
		// Arrived
		if (spy->ReachedNextWaypoint())
		{
			if (spy->GetTransform().Translation.y > 400.0f)		// At the top few waypoints (Hacked together but fast code)
			{
				m_reachedSafeZone = true;
			}
			else
			{
				// Find the waypoint that is the smallest y
				vector<Waypoint*> nextPoints = spy->m_nextWaypoint->GetNext();
				float highestY = nextPoints.front()->GetPos().y;
				spy->m_nextWaypoint = nextPoints.front();
				for (auto wpIter = nextPoints.begin(); wpIter != nextPoints.end(); ++wpIter)
				{
					Waypoint* wayPoint = (*wpIter);

					// Find the nearest waypoint
					if (highestY < wayPoint->GetTransform().Translation.y)
					{
						// Store the diff for the next check
						highestY = wayPoint->GetTransform().Translation.y;
						// Set that as the spy's target
						spy->SetNextWaypoint(wayPoint);
					}
				}
			}
		}
		else
		{
			spy->GoToNextWaypoint(dt);
		}
	}
}