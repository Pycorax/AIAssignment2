#ifndef _WAKEUPSTATE_H_
#define _WAKEUPSTATE_H_

#include "FSMState.h"
#include "Guard.h"

class WakeUpState : public FSMState
{
public:
	WakeUpState();
	virtual ~WakeUpState();

	virtual void Init(NPC* FSMOwner);
	virtual void Init(FSMState* stateOwner);
	virtual void Update(double dt);
	virtual void Exit(void);

private:
	static const float S_TIME_TO_CONSCIOUS; // Max rest time before changing back to another state
	//Guard* m_g; // Casted pointer to guard
	float m_WakeUpTimer;
	Vector3 m_scalingSpeed;
};

#endif