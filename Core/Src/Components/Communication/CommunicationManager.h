#pragma once

#include "IData.h"
#include "Controllers/CAN/CanController.h"
#include "ClockSyncronization/TimeStamp.h"
#include "ClockSyncronization/TimeController.h"

namespace Components
{
namespace Communication
{
class CommunicationManager
{
private:
	ClockSyncronization::TimeController* timeController;
	Controllers::CanController*          canController;
	ClockSyncronization::TimeStamp       globalTimeStamp;
public:
	CommunicationManager(ClockSyncronization::TimeController* timecontroller, Controllers::CanController* canController);
	virtual ~CommunicationManager();

	void initialization();
	void sendData(IData msg);
	void receiveData(void);
	bool selfTest();

};
}
}
