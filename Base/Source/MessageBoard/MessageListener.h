#ifndef _MESSAGE_LISTENER_H_
#define _MESSAGE_LISTENER_H_

#include "..\MessageBoard\Message.h"

class MessageListener
{
public:
	MessageListener();
	~MessageListener();

private:
	vector<Message*> m_messageList;
};

#endif