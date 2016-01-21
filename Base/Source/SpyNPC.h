#ifndef SPY_NPC_H
#define SPY_NPC_H

// Inheritance Includes
#include "NPC.h"
#include "GameObject2D.h"
#include "Collider2D.h"

// Other Includes
#include <vector>
#include "Guard.h"

// Using Directives
using std::vector;

class SpyNPC : public GameObject2D, public NPC, public Collider2D
{
	/*
	 *		State Classes Friend Declarations
	 * States should be able to access this class's properties
	 */ 
	friend class FSMState;
	friend class ToTargetState;
	friend class MoveTargetState;
	friend class SneakTargetState;
	friend class RunTargetState;
	friend class HuntingEnemyState;
	friend class RunEnemyState;
	friend class RespawnState;
	friend class RunToSpawnState;
	friend class BombState;

public:
	enum MOVE_MODE
	{
		MM_SNEAK,
		MM_SPRINT,
		MM_TOTAL
	};

protected:
	MOVE_MODE m_moveMode;
	float m_speed[MM_TOTAL];
	Waypoint* m_prevWaypoint;
	Waypoint* m_nextWaypoint;
	Vector2 m_bombTarget;
	Guard* m_guardTarget;
	bool m_onRoad;
	bool m_isTargeted;
	int m_combatRecord;

	// Stores references to waypoints
	vector<Waypoint*>* m__worldMap;

	// Stores references to guards to keep track of their status
	vector<Guard*> m_guardList;

public:
	SpyNPC();
	~SpyNPC();

	virtual void Init(Mesh* mesh, bool active, vector<Waypoint*>* _waypointMap = NULL);
	virtual void Update(double dt);
	virtual void Exit(void);

	void Kill(void);

	void SetNextWaypoint(Waypoint* wayPoint);
	void SetTarget(Vector2 bombSite);
	void SetOnRoad(bool road);
	void AddGuardWatch(Guard* guard);

	int GetCombatRecord(void) const;
	float GetDistSqrToBombTarget(void) const;
	float GetDistSqrToGuardTarget(void) const;
	bool ReachedNextWaypoint(void) const;
	bool ReachedTarget(void) const;
	bool NearTarget(float nearDistSquared = 100 * 100) const;
	Guard* NearGuard(float nearDistSquared) const;
	void SetTargetted(bool target);			// Inform the spy that he was targetted
	void GoToNearestWaypoint(void);
	void GoToNextWaypoint(double dt);

protected:
	float getCurrentSpeed(void) const;

private:
	// Function to send Collider2D the actual transforms of the child.
	virtual Transform collider2D_getTransforms(void) const;
	// Function to send Collider2D the state of the child.
	virtual bool collider2D_isActive(void) const;
	// Function to send Collider2D the normal of the child. This is for more precise box collisions. Forces CollideWith() to use forward checking collision detection if Vector3::ZERO_VECTOR was not returned by this function and getVelocity() of the other.
	virtual Vector3 collider2D_getNormal(void) const;
	// Function to send Collider2D the velocity of the child. This is for more precise box collisions. Forces CollideWith() to use forward checking collision detection if Vector3::ZERO_VECTOR was not returned by this function and getNormal() of the other.
	virtual Vector3 collider2D_getVelocity(void) const;
};

#endif