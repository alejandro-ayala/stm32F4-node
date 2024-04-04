#pragma once
#include "hardware_abstraction/Devices/Ov2460/Ov2640Ctrl.h"
#include "business_logic/Osal/QueueHandler.h"
#include <memory>

namespace business_logic
{
namespace DataHandling
{
class ImageCapturer
{
private:
	std::shared_ptr<hardware_abstraction::Devices::ICameraDevice> m_cameraControl;
	std::shared_ptr<business_logic::Osal::QueueHandler> m_CapturesQueue;

public:
	explicit ImageCapturer(const std::shared_ptr<hardware_abstraction::Devices::ICameraDevice>& cameraControl, const std::shared_ptr<business_logic::Osal::QueueHandler> capturesQueue = nullptr);
	virtual ~ImageCapturer() = default;

    void initialize();
    void stop();
	void captureImage();
	void extractImage();
};
}
}
