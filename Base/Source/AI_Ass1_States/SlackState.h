#ifndef _SLACKSTATE_H_
#define _SLACKSTATE_H_

#include "FSMState.h"
#include "Guard.h"

class SlackState : public FSMState
{
public:
	SlackState();
	virtual ~SlackState();

	virtual void Init(NPC* FSMOwner);
	virtual void Init(FSMState* stateOwner);
	virtual void Update(double dt);
	virtual void Exit(void);

private:
	enum E_SLACK_TYPES
	{
		SLACK_REST = 0,
		SLACK_SLEEP,
		NUM_SLACK,
	} m_currentState;
	static const float S_REST_MAX_TIME; // Max rest time before changing back to another state
	float SCALE_DOWN_VIEW[NUM_SLACK]; // Ratio to scale down view when this state is chosen
	//Guard* m_g; // Casted pointer to guard
	float m_slackTimer;
};

#endif