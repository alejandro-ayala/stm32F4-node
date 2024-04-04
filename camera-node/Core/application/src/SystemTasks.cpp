#include "../include/SystemTasks.h"

namespace application
{

SystemTasks::SystemTasks(const std::shared_ptr<business_logic::Communication::CommunicationManager>& commMng, const std::shared_ptr<business_logic::DataHandling::ImageCapturer>& imageCapturer, const std::shared_ptr<business_logic::ClockSyncronization::SharedClockSlaveManager>& sharedClkMng)
{
	createPoolTasks(commMng, imageCapturer, sharedClkMng);
}

void SystemTasks::createPoolTasks(const std::shared_ptr<business_logic::Communication::CommunicationManager>& commMng, const std::shared_ptr<business_logic::DataHandling::ImageCapturer>& imageCapturer, const std::shared_ptr<business_logic::ClockSyncronization::SharedClockSlaveManager>& sharedClkMng)
{
	m_clockSyncTaskHandler    = std::make_shared<business_logic::Osal::TaskHandler>(SystemTasks::syncronizationGlobalClock, "syncronizationGlobalClockTask", DefaultPriorityTask, static_cast<business_logic::Osal::VoidPtr>(sharedClkMng.get()));
	m_dataHandlingTaskHandler = std::make_shared<business_logic::Osal::TaskHandler>(SystemTasks::captureImage, "readSensorsTask", DefaultPriorityTask, static_cast<business_logic::Osal::VoidPtr>(imageCapturer.get()));
	m_commTaskHandler         = std::make_shared<business_logic::Osal::TaskHandler>(SystemTasks::sendData, "sendDataTask", DefaultPriorityTask, static_cast<business_logic::Osal::VoidPtr>(commMng.get()));
}

void SystemTasks::captureImage(void* argument)
{
	auto imageCapturer = std::make_shared<business_logic::DataHandling::ImageCapturer>(*static_cast<business_logic::DataHandling::ImageCapturer*>(argument));

	const auto periodTimeCaptureImage = 2000;
	imageCapturer->initialize();
	/* USER CODE BEGIN 5 */
	/* Infinite loop */
	for(;;)
	{
	  imageCapturer->captureImage();
	  m_dataHandlingTaskHandler->delayUntil(periodTimeCaptureImage);
	  imageCapturer->extractImage();
	}
	/* USER CODE END 5 */
}

void SystemTasks::sendData(void* argument)
{
  /* USER CODE BEGIN 5 */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END 5 */
}

void SystemTasks::syncronizationGlobalClock(void* argument)
{
  /* USER CODE BEGIN 5 */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END 5 */
}
}
