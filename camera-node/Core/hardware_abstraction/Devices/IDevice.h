
#pragma once
#include "../Controllers/Definitions.h"
#include "stm32f4xx_hal.h"

namespace hardware_abstraction
{
namespace Devices
{
class IDevice {
public:
	IDevice() = default;
	virtual ~IDevice() = default;

	virtual void initialization() = 0;
	virtual bool selfTest()   = 0;
};
}
}
