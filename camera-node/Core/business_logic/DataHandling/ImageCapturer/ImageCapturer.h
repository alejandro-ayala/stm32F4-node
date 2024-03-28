#pragma once
#include "hardware_abstraction/Devices/Ov2460/Ov2640Ctrl.h"
#include <memory>

namespace business_logic
{
namespace DataHandling
{
class ImageCapturer
{
private:
	std::shared_ptr<hardware_abstraction::Devices::Ov2640Ctrl> m_cameraControl;

public:
	ImageCapturer();
	virtual ~ImageCapturer();

	void processImage();
	void captureImage();
    void initialize();
};
}
}
