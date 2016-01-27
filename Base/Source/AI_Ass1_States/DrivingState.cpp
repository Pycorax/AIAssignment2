#include "DrivingState.h"

#include "Car.h"
#include "SpyNPC.h"

DrivingState::DrivingState()
{
	m_stateName = "DrivingState";
}


DrivingState::~DrivingState()
{
}

void DrivingState::Update(double dt)
{
	NPCCar* car = dynamic_cast<NPCCar*>(m_FSMOwner);

	if (car)
	{
		// Variety in acceleration and deceleration
		if (car->m_speed > 100.0f && Math::GetChance(50))
		{
			car->SetSpeed(car->m_speed - car->m_accel * dt);
		}
		else
		{
			car->SetSpeed(car->m_speed + car->m_accel * dt);
		}
		car->m_transforms.Translation += Vector2(-1.0f, 0.0f) * car->m_speed * dt;

		// Reset the car to the right
		if (car->m_transforms.Translation.x < -car->m_transforms.Scale.x * 2)
		{
			car->m_transforms.Translation.x = car->m_screenRight + car->m_transforms.Scale.x;
		}

		// Kill those that stand between it and life
		vector<GameObject2D*> victims = car->m_victims;
		for (vector<GameObject2D*>::iterator vicIter = victims.begin(); vicIter != victims.end(); ++vicIter)
		{
			SpyNPC* spy = dynamic_cast<SpyNPC*>(*vicIter);
			if (spy && spy->CollideWith(car, dt))
			{
				// The rare chance that we may not kill the spy
				if (Math::GetChance(95))
				{
					spy->Kill();
				}
			}
		}
	}
}
