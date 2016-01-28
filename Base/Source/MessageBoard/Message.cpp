#include "Message.h"

#include "MessageListener.h"

const string Message::MESSAGE_TEXT[NUM_MESSAGE] =
{
	"Request Support",
	"Priority Attack",
	"Planning to Stun",
	"Guarding",
	"Martyrdom"
	"Last Words"
};

Message::Message(MessageListener* sender, MESSAGE_TYPE type)
	: m_sender(sender)
	, m_type(type)
{
}


Message::~Message()
{
}

MessageListener* Message::GetSender() const
{
	return m_sender;
}

Message::MESSAGE_TYPE Message::GetMessage() const
{
	return m_type;
}

string Message::ToString() const
{
	if (m_type == NUM_MESSAGE)
	{
		return "Null Message";
	}
	else
	{
		string str = MESSAGE_TEXT[m_type] + " from ";

		if (m_sender)
		{
			str += m_sender->GetName();
		}
		else
		{
			str += "Anonymous.";
		}

		return str;
	}
}
