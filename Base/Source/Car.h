#ifndef CAR_H
#define CAR_H

// STL Includes
#include <vector>

// Inheritance Includes
#include "GameObject2D.h"
#include "NPC.h"
#include "Collider2D.h"

// Using Directives
using std::vector;

class NPCCar : public GameObject2D, public NPC, public Collider2D
{
	/*
	*		State Classes Friend Declarations
	* States should be able to access this class's properties
	*/
	friend class FSMState;
	friend class DrivingState;

protected:
	static const float MAX_SPEED;
	float m_speed;
	float m_accel;
	float m_screenRight;
	vector<GameObject2D*> m_victims;

public:
	NPCCar();
	~NPCCar();

	void Init(Mesh* mesh, float screenRight);
	void Update(double dt);

	void AddVictim(GameObject2D* victim);
	void SetSpeed(float vel);

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