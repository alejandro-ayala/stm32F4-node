#pragma once

#include "main.h"
#include "cmsis_os.h"

namespace application
{
namespace ClockSyncronization
{
void syncronizationGlobalClock(void const * argument);
}

namespace DataHandling
{
void readSensors(void const * argument);
}

namespace Communication
{
void sendData(void const * argument);
}
}
