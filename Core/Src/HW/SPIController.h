#pragma once
#include "stm32f4xx_hal.h"
#include "IController.h"

namespace Hardware
{
class SPIController : public IController
{
private:
	SPI_HandleTypeDef hspi1;

public:
	SPIController();
	virtual ~SPIController();

	virtual void initialize() override;

	uint8_t readRegister(uint8_t address);
	void writeRegister(uint8_t address, uint8_t data);
	bool selfTest() override;
};
}
