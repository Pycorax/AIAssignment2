#ifndef _ATTACKSTATE_H_
#define _ATTACKSTATE_H_

#include "FSMState.h"
#include "Guard.h"

class AttackState : public FSMState
{
public:
	AttackState();
	virtual ~AttackState();

	virtual void Init(NPC* FSMOwner);
	virtual void Init(FSMState* stateOwner);
	virtual void Update(double dt);
	virtual void Exit(void);

private:
	static const float S_MISSING_TIMER;
	static const float S_TIME_TILL_ATTACK;

	float m_missingTimer;
	float m_attackTimer;
	bool m_reached;
	bool m_recordPoint;
	void moveToLastSeen(double dt);
};

#endif