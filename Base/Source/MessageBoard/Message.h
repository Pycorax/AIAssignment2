#ifndef _MESSAGE_H_
#define _MESSAGE_H_

// STL Includes
#include <vector>
#include <string>

// Using Directives
using std::vector;
using std::string;

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
		MSG_HEALING_SOMEONE,
		MSG_MARTYRDOM,
		MSG_LAST_WORDS,
		MSG_DEATH,
		MSG_REPLACE_HEALER,
		MSG_REPLACE_TANK,
		NUM_MESSAGE,
	};

	static const string MESSAGE_TEXT[NUM_MESSAGE];

	Message(MessageListener* sender = nullptr, MESSAGE_TYPE type = NUM_MESSAGE);
	~Message();

	MessageListener* GetSender(void) const;
	Message::MESSAGE_TYPE GetMessage(void) const;

	string ToString(void) const;

private:
	// Senders and receivers
	MessageListener* m_sender;
	MESSAGE_TYPE m_type;
};

#endif