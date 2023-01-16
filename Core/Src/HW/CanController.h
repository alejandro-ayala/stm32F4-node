#pragma once
#include "stm32f4xx_hal.h"
#include "../Communication/ICommunication.h"
#include "IController.h"


namespace Communication
{
class CanController : public ICommunication
{
private:
	CAN_HandleTypeDef _hcan1;
	CAN_TxHeaderTypeDef pHeader; //declare a specific header for message transmittions
	CAN_RxHeaderTypeDef pRxHeader; //declare header for message reception
	CAN_FilterTypeDef sFilterConfig; //declare CAN filter structure
	uint32_t TxMailbox;
	int deviceId;

public:
	CanController();
	virtual ~CanController();

	virtual void initialize() override;
	int transmitMsg(uint8_t idMsg, uint8_t *TxMsg, uint8_t msgLength) override;
	int receiveMsg(uint8_t *rxBuffer) override;
	bool selfTest() override;
};
}
