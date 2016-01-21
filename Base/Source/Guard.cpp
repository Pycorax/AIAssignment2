#include "Guard.h"

// Spy
#include "SpyNPC.h"

const float Guard::S_GUARD_PATROL_SPEED = 60.f;
const float Guard::S_GUARD_ALERT_SPEED = S_GUARD_PATROL_SPEED * 2.f;
const float Guard::S_GUARD_DRAGGING_SPEED = S_GUARD_PATROL_SPEED * 0.5f;

Guard::Guard() : m_destination(nullptr), m_lookDir(Vector2::ZERO_VECTOR), m_moveSpeed(S_GUARD_PATROL_SPEED), m_prevLocation(nullptr), m_view(nullptr), m_defaultViewRadius(0.f), m_attacked(false), m_attacker(nullptr), m_knockedOut(false), m_wakeUpSleep(false), m_target(nullptr), m_lastSeen(Vector3::ZERO_VECTOR), m_regainConscious(false), m_lastTarget(nullptr)
{
}

Guard::~Guard()
{
	if (m_view)
	{
		delete m_view;
		m_view = nullptr;
	}
}

void Guard::Init(bool active, Mesh* mesh, Waypoint* spawnPoint, Mesh* view, float viewRadius)
{
	SetMesh(mesh);
	SetActive(active);
	this->m_transforms.Translation = spawnPoint->GetPos();
	this->m_destination = this->m_prevLocation = spawnPoint;
	this->m_defaultViewRadius = viewRadius;

	if (!m_view)
	{
		m_view = new GameObject2D();
		m_view->SetMesh(view);
		m_view->SetScale(Vector2(viewRadius * 2.f, viewRadius * 2.f));
		m_view->SetPos(m_transforms.Translation);
	}

	setCurrentState(new PatrolState());
}

void Guard::Update(double dt)
{
	NPC::Update(dt);
}

void Guard::attacked(bool attacked, bool knockedOut, SpyNPC * attacker)
{
	this->m_attacked = attacked;
	this->m_knockedOut = knockedOut;
	this->m_attacker = attacker;
}

void Guard::attack(SpyNPC* target)
{
	this->m_target = target;
	this->m_lastSeen = target->GetTransform().Translation;
}

void Guard::SetDestination(Waypoint* destination)
{
	this->m_prevLocation = this->m_destination;
	this->m_destination = destination;
}

Waypoint* Guard::GetDestination()
{
	return m_destination;
}

void Guard::SetPrevLocation(Waypoint * prevLocation)
{
	this->m_prevLocation = prevLocation;
}

Waypoint * Guard::GetPrevLocation()
{
	return m_prevLocation;
}

void Guard::SetLookDir(Vector2 lookDir)
{
	this->m_lookDir = lookDir;
}

Vector2 & Guard::GetLookDir()
{
	return m_lookDir;
}

void Guard::SetMoveSpeed(float moveSpeed)
{
	this->m_moveSpeed = moveSpeed;
}

float Guard::GetMoveSpeed()
{
	return m_moveSpeed;
}

void Guard::UpdateViewPosition()
{
	Vector2 offset = (m_transforms.Scale - m_view->GetTransform().Scale) * 0.5f;
	m_view->SetPos(m_transforms.Translation + offset);
}

GameObject2D * Guard::GetView()
{
	return m_view;
}

float Guard::GetDefaultViewRadius()
{
	return m_defaultViewRadius;
}

void Guard::SetAttacked(bool attacked)
{
	this->m_attacked = attacked;
}

bool Guard::GetAttacked()
{
	return m_attacked;
}

void Guard::SetKnockedOut(bool knockedOut)
{
	this->m_knockedOut = knockedOut;
}

bool Guard::GetKnockedOut()
{
	return m_knockedOut;
}

void Guard::SetAttacker(SpyNPC * attacker)
{
	this->m_attacker = attacker;
}

SpyNPC * Guard::GetAttacker()
{
	return m_attacker;
}

void Guard::SetSleep(bool wakeUpSleep)
{
	this->m_wakeUpSleep = wakeUpSleep;
}

bool Guard::GetSleep()
{
	return m_wakeUpSleep;
}

void Guard::SetTarget(SpyNPC * target)
{
	if (!target) // Setting target to null
	{
		if (this->m_lastTarget)
		{
			if (this->m_target)
			{
				this->m_lastTarget = this->m_target; // Assign last seen target
				this->m_target->SetTargetted(false);
			}
		}
		else
		{
			this->m_lastTarget = this->m_target; // Assign last seen target
		}
	}
	this->m_target = target;
}

SpyNPC * Guard::GetTarget()
{
	return m_target;
}

void Guard::SetLastTarget(SpyNPC * lastTarget)
{
	this->m_lastTarget = lastTarget;
}

SpyNPC * Guard::GetLastTarget()
{
	return m_lastTarget;
}

Vector3 Guard::GetLastSeen()
{
	return m_lastSeen;
}

void Guard::AddToFallback(Vector3 point)
{
	m_fallbacks.push(point);
}

std::stack<Vector3>& Guard::GetFallbacks()
{
	return m_fallbacks;
}

void Guard::SetRegainConscious(bool regainConscious)
{
	this->m_regainConscious = regainConscious;
}

bool Guard::GetRegainConscious()
{
	return m_regainConscious;
}

Transform Guard::collider2D_getTransforms(void) const
{
	return m_transforms;
}

bool Guard::collider2D_isActive(void) const
{
	return m_active;
}

Vector3 Guard::collider2D_getNormal(void) const
{
	return Vector3::ZERO_VECTOR;
}

Vector3 Guard::collider2D_getVelocity(void) const
{
	return Vector3::ZERO_VECTOR;
}
