#ifndef MESSAGE_LISTENER_H
#define MESSAGE_LISTENER_H

// STL Includes
#include <vector>

// Other Includes
#include "Message.h"

// Using Directives
using std::vector;

// Forward Declarations
class MessageBoard;

class MessageListener
{
private:
	string m_name;
	MessageBoard* m_messageBoard;		// Pointer to the message board that it is registered to
	vector<Message> m_messageList;

public:
	MessageListener(string name = "");
	~MessageListener();

	void Init(MessageBoard* mb);
	void AddMessage(Message message);
	virtual string GetName(void) const;

protected:
	// Call this function when you want to check for and react to messages
	void HandleMessage();	

	// Sending
	void sendMessage(Message::MESSAGE_TYPE type);
	void sendMessage(Message::MESSAGE_TYPE type, vector<MessageListener*> recepients);

	// Peeking at Messages
	Message peekTopMessage();
	Message* containsMessage(Message::MESSAGE_TYPE type);

private:
	// Override this function to define what happens when a message is received
	virtual void handleMessage(Message msg) = 0;
};

#endif