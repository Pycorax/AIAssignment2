#include "Message.h"



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
