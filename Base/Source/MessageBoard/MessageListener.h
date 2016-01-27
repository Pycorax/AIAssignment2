#ifndef MESSAGE_LISTENER_H
#define MESSAGE_LISTENER_H

// STL Includes
#include <queue>

// Other Includes
#include "Message.h"

// Using Directives
using std::queue;

// Forward Declarations
class MessageBoard;

class MessageListener
{
private:
	MessageBoard* m_messageBoard;		// Pointer to the message board that it is registered to
	queue<Message> m_messageList;

public:
	MessageListener();
	~MessageListener();

	void AddMessage(Message message);

protected:
	// Call this function when you want to check for and react to messages
	void HandleMessage();	

	// Sending
	void sendMessage(Message::MESSAGE_TYPE type);
	void sendMessage(Message::MESSAGE_TYPE type, vector<MessageListener*> recepients);

	// Peeking at Messages
	Message::MESSAGE_TYPE peekTopMessage();

private:
	// Override this function to define what happens when a message is received
	virtual void handleMessage(Message msg) = 0;
};

#endif