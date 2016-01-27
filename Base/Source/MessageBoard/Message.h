#ifndef _MESSAGE_H_
#define _MESSAGE_H_

// STL Includes
#include <vector>

// Using Directives
using std::vector;

// Forward Declarations
class MessageListener;

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

	Message(MessageListener* sender = nullptr, MESSAGE_TYPE type = NUM_MESSAGE);
	~Message();

	MessageListener* GetSender(void) const;
	Message::MESSAGE_TYPE GetMessage(void) const;

private:
	// Senders and receivers
	MessageListener* m_sender;
	MESSAGE_TYPE m_type;
};

#endif