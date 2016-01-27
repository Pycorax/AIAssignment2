#ifndef _PATROL_H_
#define _PATROL_H_

#include "FSMState.h"

// Include for dynamic casting
#include "Guard.h"

class PatrolState : public FSMState
{
public:
	PatrolState();
	virtual ~PatrolState();

	virtual void Init(NPC* FSMOwner);
	virtual void Init(FSMState* stateOwner);
	virtual void Update(double dt);
	virtual void Exit(void);

private:
	void calculateNewDestination();
	bool moveToDestination(double dt);
	bool moveToFallback(double dt);

private:
	enum E_UPDATE_MOVE_STATE
	{
		E_NOTHING = 0,
		E_CHANG_SPEED,
		E_REST,
	};

	static const float S_TIME_TO_CHANGE_SPEED_MIN; // Time till guard starts to attempt to slow down
	static const float S_TIME_TO_CHANGE_SPEED_MAX; // Time till guard starts to attempt to slow down
	static const float S_TIME_TO_REST_MIN;		// Time till guard starts to attempt to rest
	static const float S_TIME_TO_REST_MAX;		// Time till guard starts to attempt to rest

	//Guard* m_g; // Casted pointer to guard
	float m_timeToChangeSpeed;
	float m_timeToRest;
	bool m_rest;
	bool m_justSlowDown;
	float m_patrolTimer;
	float m_slowDownTimer;
};

#endif