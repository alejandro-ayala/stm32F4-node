#pragma once

#include "Controllers/CAN/CanController.h"
#include "ClockSyncronization/TimeController.h"
#include "TimeStamp.h"

namespace Components
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
