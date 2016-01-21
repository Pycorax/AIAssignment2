#include "RetreatState.h"
#include "SpyNPC.h"

RetreatState::RetreatState(Vector2 dangerZone) : FSMState(), m_dangerZone(dangerZone)
{
	m_stateName = "Retreat State";
}


RetreatState::~RetreatState()
{
}

void RetreatState::Init(NPC * FSMOwner)
{
	FSMState::Init(FSMOwner);

	// Set up the child state
}

void RetreatState::Init(FSMState * stateOwner)
{
	// Attach the handle to the state owner
	FSMState::Init(stateOwner);

	// Get the actual NPC-type pointer
	Guard* g = dynamic_cast<Guard*>(m_FSMOwner);

	// Check if the NPC is legit
	if (!g)
	{
		return;
	}

	if (g->GetPrevLocation())
	{
		g->SetDestination(g->GetPrevLocation()); // First call for retreat is to move back to the previous location as enemy was not spotted before
		if (g->GetDestination()->GetPos() != g->GetTransform().Translation)
		{
			g->SetLookDir((g->GetDestination()->GetPos() - g->GetTransform().Translation).Normalized());
		}
	}
}

void RetreatState::Update(double dt)
{
	FSMState::Update(dt);

	Guard* g = dynamic_cast<Guard*>(m_FSMOwner);

	// Check if the NPC is legit
	if (!g)
	{
		return;
	}

	if (g->GetAttacked() && g->GetKnockedOut())
	{
		changeState(new KnockOutState());
		return;
	}

	if (g->GetDestination()->GetPos() == g->GetTransform().Translation) // Reached destination
	{
		calcRetreatDestination();
	}
	else
	{
		moveToDestination(dt);
	}
}

void RetreatState::Exit(void)
{
}

bool RetreatState::moveToDestination(double dt)
{
	Guard* g = dynamic_cast<Guard*>(m_FSMOwner);
	if (!g)
	{
		return false;
	}

	float distFromWaypoint = (g->GetTransform().Translation - g->GetDestination()->GetPos()).LengthSquared();
	float movement = g->GetMoveSpeed() * dt;
	float movementSquared = movement * movement;

	if (movementSquared > distFromWaypoint) // Walk past waypoint
	{
		g->SetPos(g->GetDestination()->GetPos());
		g->UpdateViewPosition();
	}
	else
	{
		g->SetPos(g->GetTransform().Translation + (g->GetLookDir() * movement));
		g->UpdateViewPosition();
	}
	return true;
}

void RetreatState::calcRetreatDestination()
{
	Guard* g = dynamic_cast<Guard*>(m_FSMOwner);
	if (!g)
	{
		return;
	}

	float longestDist = 0.f;
	Waypoint* nextWaypoint;
	Waypoint* prevLocation = g->GetPrevLocation();

	if (g->GetAttacker()) // Attacker found
	{
		// Loop through all the available points and see which is furthest away from attacker
		vector<Waypoint*> waypointList = g->GetDestination()->GetNext();
		for (vector<Waypoint*>::iterator it = waypointList.begin(); it != waypointList.end(); ++it)
		{
			Waypoint* wp = *it;
			SpyNPC* s = g->GetAttacker();
			float tempDist = (wp->GetTransform().Translation - s->GetTransform().Translation).LengthSquared();
			if (wp != prevLocation && tempDist >= longestDist)
			{
				longestDist = tempDist;
				nextWaypoint = wp;
			}
		}
	}
	else // No attacker found, run away from location where guard got attacked
	{
		// Loop through all the available points and see which is furthest away from danger zone
		vector<Waypoint*> waypointList = g->GetDestination()->GetNext();
		for (vector<Waypoint*>::iterator it = waypointList.begin(); it != waypointList.end(); ++it)
		{
			Waypoint* wp = *it;
			float tempDist = (wp->GetTransform().Translation - m_dangerZone).LengthSquared();
			if (wp != prevLocation && tempDist >= longestDist)
			{
				longestDist = tempDist;
				nextWaypoint = wp;
			}
		}
	}

	g->SetPrevLocation(g->GetDestination()); // Set previous location before getting new destination

	g->SetDestination(nextWaypoint);
	g->SetLookDir((g->GetDestination()->GetPos() - g->GetTransform().Translation).Normalized());
}
