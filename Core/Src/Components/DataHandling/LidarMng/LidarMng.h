#pragma once
#include "stm32f4xx_hal.h"

namespace Components
{
namespace DataHandling
{
class LidarMng
{
private:
	int deviceId;

public:
	LidarMng();
	virtual ~LidarMng();

    void initialize();
	void readValue();
	bool selfTest();
};
}
}
