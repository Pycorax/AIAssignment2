#include "MessageListener.h"

#include "MessagePacket.h"
#include "MessageBoard.h"

MessageListener::MessageListener()
{
}


MessageListener::~MessageListener()
{
}

void MessageListener::Init(MessageBoard * mb)
{
	m_messageBoard = mb;
}

void MessageListener::AddMessage(Message message)
{
	m_messageList.push(message);
}

void MessageListener::HandleMessage()
{
	if (m_messageList.size() > 0)
	{
		// Handle the message
		handleMessage(m_messageList.back());

		// Remove the message
		m_messageList.pop();
	}
}

void MessageListener::sendMessage(Message::MESSAGE_TYPE type)
{
	// Create a message packet
	MessagePacket msg;
	msg.message = Message(this, type);

	m_messageBoard->SendMessage(msg);
}

void MessageListener::sendMessage(Message::MESSAGE_TYPE type, vector<MessageListener*> recepients)
{
	// Create a message packet
	MessagePacket msg;
	msg.message = Message(this, type);

	// Add recepients
	for (auto recepient : recepients)
	{
		msg.AddRecepient(recepient);
	}

	m_messageBoard->SendMessage(msg);
}

Message MessageListener::peekTopMessage()
{
	if (m_messageList.size() == 0)
	{
		return Message();
	}
	else
	{
		return m_messageList.back();
	}
}
