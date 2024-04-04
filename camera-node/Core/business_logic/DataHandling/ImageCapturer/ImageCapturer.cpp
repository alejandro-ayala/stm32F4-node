#include <business_logic/DataHandling/ImageCapturer/ImageCapturer.h>
#include "services/Exception/SystemExceptions.h"

namespace business_logic
{
namespace DataHandling
{
ImageCapturer::ImageCapturer(const std::shared_ptr<hardware_abstraction::Devices::ICameraDevice>& cameraControl, const std::shared_ptr<business_logic::Osal::QueueHandler> capturesQueue) : m_cameraControl(cameraControl), m_CapturesQueue(capturesQueue)
{
	BUSINESS_LOGIC_ASSERT( m_CapturesQueue->getAvailableSpace() != 0, services::BusinessLogicErrorId::QueueIsFull, "Queue to store the camera images is full");
}

void ImageCapturer::initialize()
{
	m_cameraControl->initialization();
	m_cameraControl->configuration(hardware_abstraction::Devices::CameraResolution::RES_320X240);
}

void ImageCapturer::captureImage()
{
	m_cameraControl->captureSnapshot();
	//TODO add a time check for ensure that camera is not blocked during capture process.

}

void ImageCapturer::extractImage()
{
	if(!m_cameraControl->isCapturingFrame())
	{
		m_cameraControl->processCapture();
	}
	else
	{
		THROW_BUSINESS_LOGIC_EXCEPTION(services::BusinessLogicErrorId::CameraTimeout, "Camera timeout while capturing image");
	}
}

void ImageCapturer::stop()
{
	m_cameraControl->stopCapture();
}
}
}
