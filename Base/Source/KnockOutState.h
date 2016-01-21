#ifndef _KNOCKOUTSTATE_H_
#define _KNOCKOUTSTATE_H_

#include "FSMState.h"
#include "Guard.h"

class KnockOutState : public FSMState
{
public:
	KnockOutState();
	virtual ~KnockOutState();

	virtual void Init(NPC* FSMOwner);
	virtual void Init(FSMState* stateOwner);
	virtual void Update(double dt);
	virtual void Exit(void);

private:
	static const float S_TIME_TO_WAKE_UP; // Max rest time before changing back to another state
	//Guard* m_g; // Casted pointer to guard
	float m_KnockedOutTimer;
};

#endif