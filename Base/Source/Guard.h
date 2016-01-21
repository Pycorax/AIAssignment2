#ifndef _GUARD_H_
#define _GUARD_H_

#include "NPC.h"
#include "GameObject2D.h"
#include "Collider2D.h"
#include "Waypoint.h"
#include "PatrolState.h"
#include "SlackState.h"
#include "AttackedState.h"
#include "KnockOutState.h"
#include "WakeUpState.h"
#include "AttackState.h"

#include <stack>
using std::stack;

class SpyNPC;

class Guard : public NPC, public GameObject2D, public Collider2D
{
	friend class PatrolState;
	friend class SlackState;
	friend class AttackedState;
	friend class KnockOutState;
	friend class WakeUpState;
	friend class AttackState;

public:
	static const float S_GUARD_DRAGGING_SPEED;
	static const float S_GUARD_PATROL_SPEED;
	static const float S_GUARD_ALERT_SPEED;

private:
	// Patrol data
	Waypoint* m_prevLocation;	// Prev point stored to prevent walking backwards
	Waypoint* m_destination;	// Point to walk to (Stored in case guard loses track of surrounding, can walk back)
	Vector2 m_lookDir;			// The direction where the guard is facing/walking towards
	float m_moveSpeed;			// Movement speed
	bool m_attacked;			// To notify states to change to attacked state
	bool m_knockedOut;			// If the attack from player is a success or failure
	bool m_wakeUpSleep;			// Waking up from sleep
	SpyNPC* m_attacker;			// Person who attacked this guard
	SpyNPC* m_target;			// If attacking, the target
	SpyNPC* m_lastTarget;		// Last seen target
	Vector3 m_lastSeen;			// Last seen
	stack<Vector3> m_fallbacks; // Fall back points when moving towards last seen
	bool m_regainConscious;		// Waking up from knockout state

	// View
	GameObject2D* m_view;
	float m_defaultViewRadius;

public:
	Guard();
	virtual ~Guard();
	virtual void Init(bool active, Mesh* mesh, Waypoint* spawnPoint, Mesh* view, float viewRadius);
	virtual void Update(double dt);

	void attacked(bool attacked = true, bool knockedOut = false, SpyNPC* attacker = nullptr); // Attacked by someone
	void attack(SpyNPC* target); // Attack someone

	// Setters and Getters
	void SetDestination(Waypoint* destination);
	Waypoint* GetDestination();

	void SetPrevLocation(Waypoint* prevLocation);
	Waypoint* GetPrevLocation();

	void SetLookDir(Vector2 lookDir);
	Vector2& GetLookDir();

	void SetMoveSpeed(float moveSpeed);
	float GetMoveSpeed();

	void UpdateViewPosition();

	GameObject2D* GetView();

	float GetDefaultViewRadius();

	void SetAttacked(bool attacked);
	bool GetAttacked();

	void SetKnockedOut(bool knockedOut);
	bool GetKnockedOut();

	void SetAttacker(SpyNPC* attacker);
	SpyNPC* GetAttacker();

	void SetSleep(bool wakeUpSleep);
	bool GetSleep();

	void SetTarget(SpyNPC* target);
	SpyNPC* GetTarget();

	void SetLastTarget(SpyNPC* lastTarget);
	SpyNPC* GetLastTarget();

	Vector3 GetLastSeen();

	void AddToFallback(Vector3 point);
	stack<Vector3>& GetFallbacks();

	void SetRegainConscious(bool regainConscious);
	bool GetRegainConscious();

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