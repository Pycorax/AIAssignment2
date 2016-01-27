#ifndef MESSAGE_PACKET_H
#define MESSAGE_PACKET_H

#include "Message.h"

struct MessagePacket
{
public:
	Message message;

private:
	vector<MessageListener*> recepientsList;

public:
	MessagePacket() {}
	~MessagePacket() {}

	void AddRecepient(MessageListener* recepient)
	{
		recepientsList.push_back(recepient);
	}

	vector<MessageListener*> GetRecepients() const
	{
		return recepientsList;
	}
};

#endif