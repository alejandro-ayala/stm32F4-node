#pragma once
#include "stm32f4xx_hal.h"
#include <vector>
#include <utility>

namespace hardware_abstraction
{
namespace Devices
{
constexpr uint32_t maxBufferSize = 65535;

struct CameraCfg
{
	DCMI_HandleTypeDef hdcmi;
	DMA_HandleTypeDef hdma_dcmi;

	I2C_HandleTypeDef hi2c2;
};

enum class CameraResolution
{
	RES_160X120,
	RES_320X240,
	RES_640X480,
	RES_800x600,
	RES_1024x768,
	RES_1280x960
};

class Ov2640Ctrl
{
private:

	uint8_t m_frameBuffer[maxBufferSize] = { 0 };
	uint32_t m_resolutionSize = 15534;

	DCMI_HandleTypeDef m_hdcmi;
	DMA_HandleTypeDef m_hdma_dcmi;
	I2C_HandleTypeDef m_hi2c2;

	void setRegistersConfiguration(const std::vector<std::pair<uint8_t, uint8_t>>& registerCfg);

	short SCCB_Read(uint8_t reg_addr, uint8_t *pdata);
	short SCCB_Write(uint8_t reg_addr, uint8_t data);
public:
	Ov2640Ctrl(CameraCfg cfg);
	virtual ~Ov2640Ctrl() = default;

    void initialization();
    void configuration(CameraResolution resolution);
	void captureScreenshot();
	void startContinuousCapture();
	void stopContinuousCapture();
	void processCapture();
	void decodeCapture();
};
}
}
