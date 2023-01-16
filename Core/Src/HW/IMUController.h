#pragma once
#include "stm32f4xx_hal.h"
#include "IController.h"
#include "SPIController.h"
#include "GpioController.h"

namespace Hardware
{
class IMUController : public IController
{
private:
	SPIController*  spiControl;
	GpioController* gpioControl;
	SPI_HandleTypeDef hspi1;
	double currentRotX;
	double currentRotY;
	uint8_t spiTxBuf[2];
	uint8_t spiRxBuf[2];
	int deviceId;

public:
	IMUController();
	virtual ~IMUController();

	virtual void initialize() override;
	void readValue();
	bool selfTest() override;
};
}
