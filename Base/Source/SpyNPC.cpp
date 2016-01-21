#include "SpyNPC.h"

#include "FSMState.h"
#include "RespawnState.h"

SpyNPC::SpyNPC() : NPC()
	, m_moveMode(MM_SNEAK)
	, m_onRoad(false)
	, m_guardTarget(NULL)
	, m_prevWaypoint(NULL)
	, m_nextWaypoint(NULL)
	, m__worldMap(NULL)
	, m_isTargeted(false)
	, m_combatRecord(0)
{
}


SpyNPC::~SpyNPC()
{
}

void SpyNPC::Init(Mesh* mesh, bool active, vector<Waypoint*>* _waypointMap)
{
	SetMesh(mesh);
	SetActive(active);

	// Initialize NPC speeds
	m_speed[MM_SNEAK] = 80.0f;
	m_speed[MM_SPRINT] = 130.0f;

	// Get a reference to the waypoint map
	m__worldMap = _waypointMap;

	// Set the initial state
	setCurrentState(new RespawnState);
}

void SpyNPC::Update(double dt)
{
	// Run the FSM
	NPC::Update(dt);
}

void SpyNPC::Exit(void)
{
	// Clear the FSM
	NPC::Exit();
}

void SpyNPC::Kill(void)
{
	setCurrentState(new RespawnState);
}

void SpyNPC::SetNextWaypoint(Waypoint * wayPoint)
{
	m_prevWaypoint = m_nextWaypoint;
	m_nextWaypoint = wayPoint;
}

void SpyNPC::SetTarget(Vector2 bombSite)
{
	m_bombTarget = bombSite;
}

void SpyNPC::SetOnRoad(bool road)
{
	m_onRoad = road;
}

void SpyNPC::AddGuardWatch(Guard * guard)
{
	m_guardList.push_back(guard);
}

int SpyNPC::GetCombatRecord(void) const
{
	return m_combatRecord;
}

float SpyNPC::GetDistSqrToBombTarget(void) const
{
	return (m_bombTarget - m_transforms.Translation).LengthSquared();
}

float SpyNPC::GetDistSqrToGuardTarget(void) const
{
	return (m_guardTarget->GetTransform().Translation - m_transforms.Translation).LengthSquared();
}

bool SpyNPC::ReachedNextWaypoint(void) const
{
	static const float ACCURACY = 2.0f;
	return (m_nextWaypoint->GetPos() - m_transforms.Translation).LengthSquared() < ACCURACY;
}

bool SpyNPC::ReachedTarget(void) const
{
	static const float ACCURACY = 2.0f;
	return (m_bombTarget - m_transforms.Translation).LengthSquared() < ACCURACY;
}

bool SpyNPC::NearTarget(float nearDistSquared) const
{
	return (m_bombTarget - m_transforms.Translation).LengthSquared() < nearDistSquared;
}

Guard* SpyNPC::NearGuard(float nearDistSquared) const
{
	bool nearGuard = false;

	for (vector<Guard*>::const_iterator guardIter = m_guardList.begin(); guardIter != m_guardList.end(); ++guardIter)
	{
		Guard* guard = *guardIter;

		if ((guard->GetTransform().Translation - m_transforms.Translation).LengthSquared() < nearDistSquared)
		{
			return guard;
		}
	}

	return NULL;
}

void SpyNPC::SetTargetted(bool target)
{
	m_isTargeted = target;
}

void SpyNPC::GoToNearestWaypoint(void)
{
	// Select the nearest waypoint and go towards it
	float shortestDiff = (m_transforms.Translation - (*m__worldMap).front()->GetPos()).LengthSquared();
	m_nextWaypoint = m__worldMap->front();
	for (auto wpIter = m__worldMap->begin(); wpIter != m__worldMap->end(); ++wpIter)
	{
		Waypoint* wayPoint = (*wpIter);

		// Calculate the distance to this waypoint
		float distToWaypoint = (m_transforms.Translation - wayPoint->GetPos()).LengthSquared();

		// Find the nearest waypoint
		if (distToWaypoint < shortestDiff)
		{
			// Store the diff for the next check
			shortestDiff = distToWaypoint;
			// Set that as the spy's target
			SetNextWaypoint(wayPoint);
		}
	}
}

void SpyNPC::GoToNextWaypoint(double dt)
{
	// No destination
	if (m_nextWaypoint == NULL)
	{
		return;
	}

	Vector2 toTarget = m_nextWaypoint->GetPos() - m_transforms.Translation;

	// Arrived
	if (toTarget != Vector2::ZERO_VECTOR)
	{
		// Proceed to the target
		Vector2 dir = toTarget.Normalized();
		m_transforms.Translation += dir * getCurrentSpeed() * dt;
	}
}

float SpyNPC::getCurrentSpeed(void) const
{
	return m_speed[m_moveMode];
}

Transform SpyNPC::collider2D_getTransforms(void) const
{
	return m_transforms;
}

bool SpyNPC::collider2D_isActive(void) const
{
	return m_active;
}

Vector3 SpyNPC::collider2D_getNormal(void) const
{
	return Vector3::ZERO_VECTOR;
}

Vector3 SpyNPC::collider2D_getVelocity(void) const
{
	return Vector3::ZERO_VECTOR;
}
