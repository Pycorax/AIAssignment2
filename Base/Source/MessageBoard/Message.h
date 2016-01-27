#ifndef _MESSAGE_H_
#define _MESSAGE_H_

#include <vector>
#include "..\Character.h"

using std::vector;

class Message
{
public:
	enum MESSAGE_TYPE
	{
		MSG_REQUEST_SUPPORT,
		MSG_PRIORITY_ATTACK,
		MSG_PLAN_TO_STUN,
		MSG_GUARDING_SOMEONE,
		MSG_MARTYRDOM,
		MSG_LAST_WORDS,
		NUM_MESSAGE,
	};

	Message();
	~Message();

private:
	// Senders and receivers
	Character* m_sender;
	vector<Character*> m_receiver; // NULL if message is global

	MESSAGE_TYPE m_type;
};

#endif