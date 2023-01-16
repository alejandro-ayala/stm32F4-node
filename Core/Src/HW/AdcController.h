#pragma once
#include "stm32f4xx_hal.h"
#include "IController.h"

namespace Hardware
{
class AdcController : public IController
{
private:
	ADC_HandleTypeDef hadc1;

public:
	AdcController();
	virtual ~AdcController();

	virtual void initialize() override;

	bool selfTest() override;
};
}
