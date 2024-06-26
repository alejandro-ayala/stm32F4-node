#pragma once

#include "../../hardware_abstraction/Controllers/CAN/CanController.h"
#include "TimeController.h"
#include "TimeStamp.h"

namespace business_logic
{
namespace ClockSyncronization
{
class SharedClockSlaveManager
{
private:
	TimeController*                timeController;
	Controllers::CanController*    canController;
	TimeStamp                      globalTimeStamp;
	TimeBaseRef                    globalTimeReference;
public:
	SharedClockSlaveManager(TimeController* timecontroller, Controllers::CanController* cancontroller);
	~SharedClockSlaveManager();
	void initialization();
	bool getGlobalTime();
	TimeStamp getTimeReference() const;
};
}
}
