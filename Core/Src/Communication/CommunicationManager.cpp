
#include "CommunicationManager.h"
#include "../HW/CanController.h"
namespace Communication
{
CommunicationManager::CommunicationManager()
{
	canController = new CanController();
}

CommunicationManager::~CommunicationManager()
{
	delete canController;
}

void CommunicationManager::initialization()
{
	canController->initialize();
}

void CommunicationManager::sendMsg()
{
	uint8_t idMsg;
	uint8_t *txMsg;
	uint8_t msgLength;
	canController->transmitMsg(idMsg,txMsg,msgLength);
}

void CommunicationManager::receiveMsg()
{
	uint8_t *rxMsg;
	canController->receiveMsg(rxMsg);
}

bool CommunicationManager::selfTest()
{
	initialization();
	bool result = canController->selfTest();

	return result;
}
}
