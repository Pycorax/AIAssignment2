#ifndef MESSAGE_BOARD_H
#define MESSAGE_BOARD_H

// STL Includes
#include <queue>

// Other Includes
#include "..\MessageBoard\MessagePacket.h"
#include "..\MessageBoard\MessageListener.h"

// Using Directives
using std::queue;

class MessageBoard
{
private:
	vector<Message> m_historyList;
	queue<Message> m_globalMessages;

	vector<MessageListener*> m_registrants; // Characters must sign up to receive message

public:
	MessageBoard();
	~MessageBoard();

	// Init
	void RegisterUser(MessageListener* listener);		// Use this function to register a character into the MessageBoard's mailing list.

	// Messaging
	bool SendMessage(MessagePacket msg);

	// Peeking
	Message PeekGlobalMessage(void) const;
};

#endif