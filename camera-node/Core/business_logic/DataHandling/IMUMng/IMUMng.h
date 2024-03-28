#pragma once
#include "stm32f4xx_hal.h"

#include "../../../hardware_abstraction/Controllers/GPIO/GpioController.h"
#include "../../../hardware_abstraction/Controllers/IController.h"
#include "../../../hardware_abstraction/Controllers/SPI/SPIController.h"

namespace Components
{
namespace DataHandling
{
class IMUMng
{
private:
	hardware_abstraction::Controllers::SPIController*  spiControl;
	hardware_abstraction::Controllers::GpioController* gpioControl;
	SPI_HandleTypeDef hspi1;
	double currentRotX;
	double currentRotY;
	uint8_t spiTxBuf[2];
	uint8_t spiRxBuf[2];
	int deviceId;

public:
	IMUMng();
	virtual ~IMUMng();

    void initialize();
	void readValue();
	bool selfTest();
};
}
}
