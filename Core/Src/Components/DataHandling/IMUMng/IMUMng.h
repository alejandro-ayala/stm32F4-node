#pragma once
#include "stm32f4xx_hal.h"

#include "Controllers/GPIO/GpioController.h"
#include "Controllers/IController.h"
#include "Controllers/SPI/SPIController.h"

namespace Components
{
namespace DataHandling
{
class IMUMng
{
private:
	Controllers::SPIController*  spiControl;
	Controllers::GpioController* gpioControl;
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
