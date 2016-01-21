#include "Car.h"

#include "DrivingState.h"

const float NPCCar::MAX_SPEED = 300.0f;

NPCCar::NPCCar() : GameObject2D(), NPC()
	, m_accel(20.0f)
	, m_speed(0.0f)
	, m_screenRight(1280.0f)
{
}


NPCCar::~NPCCar()
{
}

void NPCCar::Init(Mesh * mesh, float screenRight)
{
	GameObject2D::Init(mesh, Transform());

	// Store the screen's rightmost coord
	m_screenRight = screenRight;

	// Set up the first state
	setCurrentState(new DrivingState);
}

void NPCCar::Update(double dt)
{
	NPC::Update(dt);
}

void NPCCar::AddVictim(GameObject2D * victim)
{
	m_victims.push_back(victim);
}

void NPCCar::SetSpeed(float vel)
{
	m_speed = vel;

	if (m_speed < 0.0f)
	{
		m_speed = 0.0f;
	}
	else if (m_speed > MAX_SPEED)
	{
		m_speed = MAX_SPEED;
	}
}

Transform NPCCar::collider2D_getTransforms(void) const
{
	return m_transforms;
}

bool NPCCar::collider2D_isActive(void) const
{
	return m_active;
}

Vector3 NPCCar::collider2D_getNormal(void) const
{
	return Vector3::ZERO_VECTOR;
}

Vector3 NPCCar::collider2D_getVelocity(void) const
{
	return Vector3::ZERO_VECTOR;
}
