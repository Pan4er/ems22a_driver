#include "ems22a_driver.h"

bool EMS22ReadState(struct EMS22ADriverHandle *driverHandle, struct EMS22AState *readState) {
	bool computedParity = false;

	HAL_GPIO_WritePin(driverHandle->CSPin.GPIO, driverHandle->CSPin.Pin, GPIO_PIN_SET);
	HAL_Delay(1);
	HAL_GPIO_WritePin(driverHandle->CSPin.GPIO, driverHandle->CSPin.Pin, GPIO_PIN_RESET);
	HAL_Delay(1);

	for(int i = 0; i < POSITION_BIT_COUNT; i++) {
		readState->Position <<= 1;

		HAL_GPIO_WritePin(driverHandle->CLKPin.GPIO, driverHandle->CLKPin.Pin, GPIO_PIN_RESET);
		HAL_Delay(1);
		HAL_GPIO_WritePin(driverHandle->CLKPin.GPIO, driverHandle->CLKPin.Pin, GPIO_PIN_SET);
		HAL_Delay(1);

		GPIO_PinState pinState = HAL_GPIO_ReadPin(driverHandle->DOPin.GPIO, driverHandle->DOPin.Pin);
		if(pinState == GPIO_PIN_SET) computedParity = !computedParity;
		readState->Position |= (uint16_t)pinState;

	}

	for(int i = 0; i < FLAGS_BIT_COUNT; i++) {
        readState->Flags <<= 1;

		HAL_GPIO_WritePin(driverHandle->CLKPin.GPIO, driverHandle->CLKPin.Pin, GPIO_PIN_RESET);
		HAL_Delay(1);
		HAL_GPIO_WritePin(driverHandle->CLKPin.GPIO, driverHandle->CLKPin.Pin, GPIO_PIN_SET);
		HAL_Delay(1);

		GPIO_PinState pinState = HAL_GPIO_ReadPin(driverHandle->DOPin.GPIO, driverHandle->DOPin.Pin);
		if(pinState == GPIO_PIN_SET) computedParity = !computedParity;

		readState->Flags |= (uint16_t)pinState;
	}

	HAL_GPIO_WritePin(driverHandle->CLKPin.GPIO, driverHandle->CLKPin.Pin, GPIO_PIN_RESET);
	HAL_Delay(1);
	HAL_GPIO_WritePin(driverHandle->CLKPin.GPIO, driverHandle->CLKPin.Pin, GPIO_PIN_SET);
	HAL_Delay(1);

	bool readParity = HAL_GPIO_ReadPin(driverHandle->DOPin.GPIO, driverHandle->DOPin.Pin);

	return readParity == computedParity;
}
