#ifndef _MESSAGE_BOARD_H_
#define _MESSAGE_BOARD_H_

#include "..\MessageBoard\Message.h"
#include "..\MessageBoard\MessageListener.h"

class MessageBoard
{
public:
	MessageBoard();
	~MessageBoard();

private:
	vector<Message*> m_historyList;
	vector<Message*> m_globalList;

	vector<MessageListener*> m_characterList; // Characters must sign up to receive message
	
};

#endif