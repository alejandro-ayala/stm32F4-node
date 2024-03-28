#include "ov2640Config.h"
#include "Ov2640Ctrl.h"
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>
#include "main.h"
namespace hardware_abstraction
{
namespace Devices
{

short Ov2640Ctrl::SCCB_Write(uint8_t reg_addr, uint8_t data) {
	short opertionStatus = 0;
	uint8_t buffer[2] = { 0 };
	HAL_StatusTypeDef connectionStatus;
	buffer[0] = reg_addr;
	buffer[1] = data;
	__disable_irq();
	connectionStatus = HAL_I2C_Master_Transmit(&m_hi2c2, (uint16_t) 0x60, buffer,
			2, 100);
	if (connectionStatus == HAL_OK) {
		opertionStatus = 1;
	} else {
		opertionStatus = 0;
	}
	__enable_irq();
	return opertionStatus;
}

short Ov2640Ctrl::SCCB_Read(uint8_t reg_addr, uint8_t *pdata) {
	short opertionStatus = 0;
	HAL_StatusTypeDef connectionStatus;
	__disable_irq();
	connectionStatus = HAL_I2C_Master_Transmit(&m_hi2c2, (uint16_t) 0x60,
			&reg_addr, 1, 100);
	if (connectionStatus == HAL_OK) {
		connectionStatus = HAL_I2C_Master_Receive(&m_hi2c2, (uint16_t) 0x61, pdata,
				1, 100);
		if (connectionStatus == HAL_OK) {
			opertionStatus = 0;
		} else {
			opertionStatus = 1;
		}
	} else {
		opertionStatus = 2;
	}
	__enable_irq();
	return opertionStatus;
}

Ov2640Ctrl::Ov2640Ctrl(CameraCfg cfg) : m_hdcmi(cfg.hdcmi), m_hdma_dcmi(cfg.hdma_dcmi), m_hi2c2(cfg.hi2c2)
{

}

void Ov2640Ctrl::initialization()
{

	HAL_GPIO_WritePin(CAMERA_RESET_GPIO_Port, CAMERA_RESET_Pin, GPIO_PIN_RESET);
	HAL_Delay(100);
	HAL_GPIO_WritePin(CAMERA_RESET_GPIO_Port, CAMERA_RESET_Pin, GPIO_PIN_SET);
	HAL_Delay(100);

	//TODO add register map instead of magic values
	SCCB_Write(0xff, 0x01);
	SCCB_Write(0x12, 0x80);
	HAL_Delay(100);

	uint8_t pid;
	uint8_t ver;
	SCCB_Read(0x0a, &pid);  // pid value is 0x26
	SCCB_Read(0x0b, &ver);  // ver value is 0x42
	std::cout << "Camera PID:" << pid << " version: " << ver << std::endl;

	// Stop DCMI clear buffer
	HAL_DCMI_Stop(&m_hdcmi);
	HAL_Delay(10); //TODO check if needed
}

void Ov2640Ctrl::setRegistersConfiguration(const std::vector<std::pair<uint8_t, uint8_t>>& registerCfg)
{
	for(const auto& [regAddr, regVal] : registerCfg)
	{
		SCCB_Write(regAddr, regVal);
		std::cout << "SCCB write register: " << std::to_string(regAddr) << std::to_string(regVal) << std::endl;
		HAL_Delay(10);
		uint8_t newRegVal;
		SCCB_Read(regAddr, &newRegVal);
		if (regVal != regVal)
		{
			std::cout << "SCCB write failure: " << std::to_string(regAddr) << std::to_string(regVal) << std::endl;
		}
	}
}

void Ov2640Ctrl::configuration(CameraResolution resolution)
{
	setRegistersConfiguration(OV2640_JPEG_INIT);
	setRegistersConfiguration(OV2640_YUV422);
	setRegistersConfiguration(OV2640_JPEG);
	HAL_Delay(10);
	SCCB_Write(0xff, 0x01);
	HAL_Delay(10);
	SCCB_Write(0x15, 0x00);

	setRegistersConfiguration(OV2640_320x240_JPEG);
}

void Ov2640Ctrl::captureScreenshot()
{
	std::fill(std::begin(m_frameBuffer), std::end(m_frameBuffer), 0);;
	HAL_DCMI_Start_DMA(&m_hdcmi, DCMI_MODE_SNAPSHOT, (uint32_t)m_frameBuffer, m_resolutionSize);
	HAL_Delay(2000);
	HAL_DCMI_Suspend(&m_hdcmi);
	HAL_DCMI_Stop(&m_hdcmi);
}

void Ov2640Ctrl::processCapture()
{
	uint32_t bufferPointer = 0;
	bool headerFound;

	while (1)
	{
		if (!headerFound && m_frameBuffer[bufferPointer] == 0xFF
				&& m_frameBuffer[bufferPointer + 1] == 0xD8)
		{
			headerFound = true;
			std::cout << "Found header of JPEG file" << std::endl;
		}
		if (headerFound && m_frameBuffer[bufferPointer] == 0xFF
				&& m_frameBuffer[bufferPointer + 1] == 0xD9)
		{
			bufferPointer = bufferPointer + 2;
			std::cout << "Found EOI of JPEG file" << std::endl;
			headerFound = false;
			break;
		}
		if (bufferPointer >= maxBufferSize)
		{
			break;
		}
		bufferPointer++;
	}
	std::cout << "Image size:" << std::to_string(bufferPointer) << " bytes" << std::endl;
}

void Ov2640Ctrl::decodeCapture()
{

//	ov2640_decodeJPEG(m_frameBuffer, bufferPointer, 1); // Image decoding, grayscale selection.
//	HAL_Delay(300);
//	ov2640_encodeJPEG(&imageBuffer, &imageSize, 16); // Encoding image with quality set to 16%.
//	//HAL_UART_Transmit_DMA(&huart3, imageBuffer, imageSize); // Sending buffer to UART data output.
//	HAL_Delay(300);
}

void Ov2640Ctrl::startContinuousCapture()
{

}

void Ov2640Ctrl::stopContinuousCapture()
{

}

}
}
