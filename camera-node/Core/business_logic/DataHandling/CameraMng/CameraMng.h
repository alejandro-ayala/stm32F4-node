#pragma once
#include "stm32f4xx_hal.h"

namespace business_logic
{
namespace DataHandling
{
class CameraMng
{
private:
	int deviceId;

public:
	CameraMng();
	virtual ~CameraMng() = default;

    void initialize();
	void readValue();
	bool selfTest();
};
}
}
