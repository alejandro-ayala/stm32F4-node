#include "IMUMng.h"
#include <math.h>

namespace Components
{
namespace DataHandling
{
IMUMng::IMUMng()
{
	spiControl  = new Controllers::SPIController();
	gpioControl = new Controllers::GpioController();
}

IMUMng::~IMUMng()
{
	delete spiControl;
	delete gpioControl;
}

void IMUMng::initialize()
{
	/*To transmit data in SPI follow the next steps: */
	// 1. Bring slave select to low
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_3, GPIO_PIN_RESET);
	// 2. Transmit register + data
	spiTxBuf[0] = 0x20; // control Register
	spiTxBuf[1] = 0x17; //Data  Enable X Y Z Rate 3.125 Hz --- Valor original = 0x11
	//               size, timeout
	HAL_SPI_Transmit(&hspi1, spiTxBuf, 2, 50);
	// 3. Bring slave select high
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_3, GPIO_PIN_SET);

	/*To receive data in SPI follow the next steps: */
	// 1.Bring slave select low
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_3, GPIO_PIN_RESET);
	// 2.Transmit register + 0x80 (To set MSB high) Most Significant Bit(MSB) high = read mode
	spiTxBuf[0] = 0x20|0x80; //Register
	HAL_SPI_Transmit(&hspi1, spiTxBuf, 1, 50);
	// 3.Receive data
	HAL_SPI_Receive(&hspi1, spiRxBuf, 1, 50);
	// 4.Bring slave select high
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_3, GPIO_PIN_SET);
}

void IMUMng::readValue()
{
	uint8_t ix1 = spiControl->readRegister(0x28);//SPI_Read (0x28);
	uint8_t ix2 = spiControl->readRegister(0x29);
	uint8_t ix = (ix2<< 8) + ix1;
	if (ix >= 0x8000) ix = -(65536 - ix);
	uint8_t x = ix/16384.0;

	uint8_t iy1 = spiControl->readRegister(0x2A);
	uint8_t iy2 = spiControl->readRegister(0x2B);
	uint8_t iy = (iy2 << 8) + iy1;
	if (iy >= 0x8000) iy = -(65536 - iy);
	double y = iy/16384.0;

	uint8_t iz1 = spiControl->readRegister(0x2C);
	uint8_t iz2 = spiControl->readRegister(0x2D);
	double iz = (iz2 << 8) + iz1;
	if (iz >= 0x8000) iz = -(65536 - iz);
	double z = iz/16384.0;

	currentRotX = atan2(y, sqrt(x*x+z*z)) * 180.0/3.1416;
	currentRotY = - atan2(x, sqrt(y*y+z*z)) * 180.0/3.1416;
}

bool IMUMng::selfTest()
{
	return true;
}
}
}
