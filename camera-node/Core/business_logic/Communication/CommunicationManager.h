#pragma once

#include "../../hardware_abstraction/Controllers/CAN/CanController.h"
#include "IData.h"
#include "../ClockSyncronization/TimeStamp.h"
#include "../ClockSyncronization/TimeController.h"

namespace business_logic
{
namespace Communication
{
class CommunicationManager
{
private:
	ClockSyncronization::TimeController* timeController;
	hardware_abstraction::Controllers::CanController*          canController;
	ClockSyncronization::TimeStamp       globalTimeStamp;
public:
	CommunicationManager(ClockSyncronization::TimeController* timecontroller, hardware_abstraction::Controllers::CanController* canController);
	virtual ~CommunicationManager();

	void initialization();
	void sendData(IData msg);
	void receiveData(void);
	bool selfTest();

};
}
}
