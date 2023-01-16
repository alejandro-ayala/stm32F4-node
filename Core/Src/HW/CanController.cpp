#include "CanController.h"

using namespace Hardware;
namespace Communication
{

CanController::CanController() : ICommunication("CanController")
{

}

CanController::~CanController()
{

}

void CanController::initialize()
{
	_hcan1.Instance = CAN1;
	_hcan1.Init.Prescaler = 21;
	_hcan1.Init.Mode = CAN_MODE_NORMAL;
	_hcan1.Init.SyncJumpWidth = CAN_SJW_1TQ;
	_hcan1.Init.TimeSeg1 = CAN_BS1_12TQ;
	_hcan1.Init.TimeSeg2 = CAN_BS2_4TQ;
	_hcan1.Init.TimeTriggeredMode = DISABLE;
	_hcan1.Init.AutoBusOff = DISABLE;
	_hcan1.Init.AutoWakeUp = DISABLE;
	_hcan1.Init.AutoRetransmission = DISABLE;
	_hcan1.Init.ReceiveFifoLocked = DISABLE;
	_hcan1.Init.TransmitFifoPriority = DISABLE;
	if (HAL_CAN_Init(&_hcan1) != HAL_OK)
	{
		//Error_Handler();
	}

	pHeader.DLC=1; //give message size of 1 byte
	pHeader.IDE=CAN_ID_STD; //set identifier to standard
	pHeader.RTR=CAN_RTR_DATA; //set data type to remote transmission request?
	pHeader.StdId=0x2F4; //define a standard identifier, used for message identification by filters (##switch this for the other microcontroller##)

	//filter one (stack light blink)
	sFilterConfig.FilterFIFOAssignment=CAN_FILTER_FIFO0; //set fifo assignment
	sFilterConfig.FilterIdHigh=0x2FF<<5; //the ID that the filter looks for (##switch this for the other microcontroller##)
	sFilterConfig.FilterIdLow=0;
	sFilterConfig.FilterMaskIdHigh=0;
	sFilterConfig.FilterMaskIdLow=0;
	sFilterConfig.FilterScale=CAN_FILTERSCALE_32BIT; //set filter scale
	sFilterConfig.FilterActivation=ENABLE;

	HAL_CAN_ConfigFilter(&_hcan1, &sFilterConfig); //configure CAN filter

	HAL_CAN_Start(&_hcan1); //start CAN
	HAL_CAN_ActivateNotification(&_hcan1, CAN_IT_RX_FIFO0_MSG_PENDING); //enable interrupts
}

int CanController::transmitMsg(uint8_t idMsg, uint8_t *TxMsg, uint8_t msgLength)
{

	HAL_CAN_AddTxMessage(&_hcan1, &pHeader, TxMsg, &TxMailbox);
}

int CanController::receiveMsg(uint8_t *rxBuffer)
{
	return 1;
}

bool CanController::selfTest()
{
	return true;
}
}
