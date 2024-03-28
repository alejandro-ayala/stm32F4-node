#include "SPIController.h"

namespace hardware_abstraction
{
namespace Controllers
{

SPIController::SPIController() : IController("SPIController")
{

}

SPIController::~SPIController()
{

}

void SPIController::initialize()
{
	hspi1.Instance = SPI1;
	hspi1.Init.Mode = SPI_MODE_MASTER;
	hspi1.Init.Direction = SPI_DIRECTION_2LINES;
	hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
	hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
	hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
	hspi1.Init.NSS = SPI_NSS_SOFT;
	hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
	hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
	hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
	hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
	hspi1.Init.CRCPolynomial = 10;
	if (HAL_SPI_Init(&hspi1) != HAL_OK)
	{
		//Error_Handler();
	}
}

uint8_t SPIController::readRegister(uint8_t address)
{
	uint8_t spiTxBuf[2], spiRxBuf[2];
	// 1.Bring slave select low
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_3, GPIO_PIN_RESET);
	// 2.Transmit register + 0x80 (To set MSB high) Most Significant Bit(MSB) high = read mode
	spiTxBuf[0] = address|0x80; //Register
	HAL_SPI_Transmit(&hspi1, spiTxBuf, 1, 50);
	// 3.Receive data
	HAL_SPI_Receive(&hspi1, spiRxBuf, 1, 50);
	// 4.Bring slave select high
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_3, GPIO_PIN_SET);

	return spiRxBuf[0];
}

void SPIController::writeRegister(uint8_t address, uint8_t data)
{
	uint8_t spiTxBuf[2];
	/*To transmit data in SPI follow the next steps: */
	// 1. Bring slave select to low
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_3, GPIO_PIN_RESET);
	// 2. Transmit register + data
	spiTxBuf[0] = address; // control Register
	spiTxBuf[1] = data; //Data  Enable X Y Z Rate 3.125 Hz --- Valor original = 0x11
	//               size, timeout
	HAL_SPI_Transmit(&hspi1, spiTxBuf, 2, 50);
	// 3. Bring slave select high
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_3, GPIO_PIN_SET);
}

bool SPIController::selfTest()
{
	return true;
}
}
}
