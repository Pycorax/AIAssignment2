#ifndef _MESSAGE_BOARD_H_
#define _MESSAGE_BOARD_H_

#include "..\MessageBoard\Message.h"

class MessageBoard
{
public:
	MessageBoard();
	~MessageBoard();

private:
	vector<Message*> m_historyList;
	vector<Message*> m_globalList;

	vector<Character*> m_characterList; // Characters must sign up to receive message
	
};

#endif