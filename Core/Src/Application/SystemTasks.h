#pragma once

#include "main.h"
#include "cmsis_os.h"

namespace Application
{
namespace DataHandling
{
void readSensors(void const * argument);
void sendData(void const * argument);
}
}
