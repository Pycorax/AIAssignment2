#ifndef _RETREATSTATE_H_
#define _RETREATSTATE_H_

#include "FSMState.h"
#include "Guard.h"

class RetreatState : public FSMState
{
public:
	RetreatState(Vector2 dangerZone);
	virtual ~RetreatState();

	virtual void Init(NPC* FSMOwner);
	virtual void Init(FSMState* stateOwner);
	virtual void Update(double dt);
	virtual void Exit(void);

private:
	bool moveToDestination(double dt);
	void calcRetreatDestination();

	Vector2 m_dangerZone; // Point where guard was attacked
};

#endif