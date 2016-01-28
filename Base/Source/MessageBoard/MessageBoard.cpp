#include "MessageBoard.h"



MessageBoard::MessageBoard()
{
}


MessageBoard::~MessageBoard()
{
}

void MessageBoard::RegisterUser(MessageListener * listener)
{
	if (listener)
	{
		// Provide it with a pointer to this so that it can send messages
		listener->Init(this);

		// Add this into the registration list
		m_registrants.push_back(listener);
	}
}

bool MessageBoard::SendMessage(MessagePacket msg)
{
	// Determine the type of message
	if (msg.GetRecepients().size() > 0)
	{
		// Non-Global message
		// -- Forward it to the recepients
		auto recepientList = msg.GetRecepients();
		for (auto recepient : recepientList)
		{
			recepient->AddMessage(msg.message);
		}
	}
	else
	{
		// Global message
		m_globalMessages.push(msg.message);

		// -- Send it to everyone
		for (auto recepient : m_registrants)
		{
			recepient->AddMessage(msg.message);
		}
	}

	return false;
}
