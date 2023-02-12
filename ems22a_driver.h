#pragma once

#include "stdint.h"
#include "stdbool.h"

#include "gpio.h"

#define POSITION_BIT_COUNT 10
#define FLAGS_BIT_COUNT 5

struct GPIOPin {
    GPIO_TypeDef *GPIO;
    uint16_t Pin;
};

struct EMS22ADriverHandle {
    struct GPIOPin CLKPin;
    struct GPIOPin DOPin;
    struct GPIOPin CSPin;
};

struct EMS22AState {
    uint16_t Position;
    uint8_t Flags;
};

bool EMS22ReadState(struct EMS22ADriverHandle *driverHandle, struct EMS22AState *readState);
