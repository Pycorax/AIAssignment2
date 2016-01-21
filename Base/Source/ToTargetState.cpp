#include "ToTargetState.h"

#include "SneakTargetState.h"
#include "RunTargetState.h"
#include "BombState.h"
#include "HuntingEnemyState.h"
#include "RunToSpawnState.h"
#include "MyMath.h"
#include "SpyNPC.h"

const float ToTargetState::NEAR_DIST_TO_GUARD_SQUARED = 200.0f * 200.0f;
const float ToTargetState::ATTACK_GUARD_POLL_TIME = 5.0f;

struct WaypointPacket
{
	Waypoint* wp;
	float distToWaypoint;
	int probability;

	WaypointPacket(Waypoint* _wp, float dist, int prob = 0)
	{
		wp = _wp;
		distToWaypoint = dist;
		probability = prob;
	}
};

ToTargetState::ToTargetState() : FSMState()
	, m_timeSinceLastPoll(0.0f)
{
	m_stateName = "ToTargetState";
}


ToTargetState::~ToTargetState()
{
}

void ToTargetState::Init(NPC * FSMOwner)
{
	FSMState::Init(FSMOwner);
	
	// Get a handle to the spy
	SpyNPC* spy = dynamic_cast<SpyNPC*>(m_FSMOwner);

	if (spy)
	{
		// Set up the child state
		setCurrentState(new RunTargetState);

		// First waypoint should be decided before coming in here
		if (spy->m_nextWaypoint == NULL)
		{
			spy->GoToNearestWaypoint();
		}
	}
}

void ToTargetState::Init(FSMState * state)
{
	FSMState::Init(state);

	// Get a handle to the spy
	SpyNPC* spy = dynamic_cast<SpyNPC*>(m_FSMOwner);

	if (spy)
	{
		// Set up the child state
		setCurrentState(new RunTargetState);

		// First waypoint should be decided before coming in here
		if (spy->m_nextWaypoint == NULL)
		{
			spy->GoToNearestWaypoint();
		}
	}
}

void ToTargetState::Update(double dt)
{
	// Run the child state
	FSMState::Update(dt);

	// Update the polling timer
	m_timeSinceLastPoll += dt;

	// Get a handle to the spy
	SpyNPC* spy = dynamic_cast<SpyNPC*>(m_FSMOwner);

	if (spy)
	{
		// Trigger Conditions here
		if (spy->m_isTargeted)
		{
			changeState(new RunToSpawnState);
		}
		
		if (spy->ReachedNextWaypoint())
		{
			if (spy->ReachedTarget())
			{
				changeState(new BombState);
			}
			else
			{
				// Find the distances between the waypoint and the bomb and store them inside a WaypointPacket
				vector<Waypoint*> nextPoints = spy->m_nextWaypoint->GetNext();
				vector<WaypointPacket> waypoints;
				float shortest;
				bool first = true;
				for (auto wpIter = nextPoints.begin(); wpIter != nextPoints.end(); ++wpIter)
				{
					Waypoint* wayPoint = (*wpIter);


					// Don't backtrack
					if (wayPoint == spy->m_nextWaypoint)
					{
						// This will have no chance
						continue;
					}

					// Calculate the total distance to reach the bomb from this waypoint
					float distToWaypoint = (spy->m_bombTarget - wayPoint->GetPos()).LengthSquared() + (wayPoint->GetPos() - spy->GetTransform().Translation).LengthSquared();

					// Use this as a point of reference
					if (first || distToWaypoint < shortest)
					{
						shortest = distToWaypoint;

						// This is the bomb if it's true
						if (shortest <= 0.0f)
						{

						}

						first = false;
					}

					// // Stuff this into a packet
					waypoints.push_back(WaypointPacket(wayPoint, distToWaypoint));
				}

				// Assign probabilities for each Waypoint
				const float MAX_CHANCE = 100.0f;
				for (auto packet = waypoints.begin(); packet != waypoints.end(); ++packet)
				{
					packet->probability = static_cast<int>(MAX_CHANCE * shortest / packet->distToWaypoint);
				}

				// Sort the probabilities
				vector<WaypointPacket> sortedProbabilities;
				while (waypoints.size() > 0)
				{
					vector<WaypointPacket>::iterator lowest = waypoints.begin();
					for (auto packet = waypoints.begin(); packet != waypoints.end(); ++packet)
					{
						if (packet->probability < lowest->probability)
						{
							lowest = packet;
						}
					}
					sortedProbabilities.push_back(*lowest);
					waypoints.erase(lowest);
				}

				// Roll the die
				int chance = Math::GetRandomChance();
				for (auto packet = sortedProbabilities.begin(); packet != sortedProbabilities.end(); ++packet)
				{
					if (chance < packet->probability)
					{
						// Set that as the spy's target
						spy->SetNextWaypoint(packet->wp);
						break;
					}
				}
			}
		}
		else if (m_timeSinceLastPoll > ATTACK_GUARD_POLL_TIME && !spy->NearTarget())		// If we're so close to our objective, don't bother
		{
			Guard* nearGuard = spy->NearGuard(NEAR_DIST_TO_GUARD_SQUARED);
			if (nearGuard && !nearGuard->GetKnockedOut() && Math::GetChance(CHANCE_ATTACK_WHEN_NEAR))
			{
				spy->m_guardTarget = nearGuard;
				changeState(new HuntingEnemyState);
			}
		}
	}
}

void ToTargetState::Exit(void)
{
	FSMState::Exit();
}
