#pragma once
#include "ICommunication.h"
namespace Communication
{
class CommunicationManager
{
private:
	ICommunication* canController;
public:
	CommunicationManager();
	virtual ~CommunicationManager();

	void initialization();
	void syncSharedClock(void);
	void sendMsg();
	void receiveMsg();
	bool selfTest();
};
}
