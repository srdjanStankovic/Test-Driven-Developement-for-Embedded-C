#include <stdbool.h>
#include "LedDriver.h"
#include "../include/util/RuntimeError.h"

enum
{
	 ALL_LEDS_ON = ~0,
	 ALL_LEDS_OFF = ~ALL_LEDS_ON
};

enum
{
	FIRST_LED = 1,
	LAST_LED = 16
};

static uint16_t * ledsAddress;
static uint16_t ledsImage;

static void updateHardware(void)
{
	*ledsAddress = ledsImage;
}

static uint16_t convretLedNumberToBit(int ledNumber)
{
	return (1 << (ledNumber -1) );
}

static _Bool IsLedOutOfBounds(int ledNumber)
{
	return (ledNumber<FIRST_LED) || (ledNumber>LAST_LED);
}

static void setLedImageBit(int ledNumber)
{
	ledsImage |= convretLedNumberToBit(ledNumber);
}

static void clearLedImageBit(int ledNumber)
{
	ledsImage &= ~convretLedNumberToBit(ledNumber);
}

void LedDriver_Create(uint16_t * address)
{
	ledsAddress = address;
	ledsImage = ALL_LEDS_OFF;
	updateHardware();
}

void LedDriver_Destroy(void)
{

}

void LedDriver_TurnOn(int ledNumber)
{
	if(IsLedOutOfBounds(ledNumber))
	{
		RUNTIME_ERROR("LED Driver: out-of-bound LED", ledNumber);
		return;
	}

	setLedImageBit(ledNumber);
	updateHardware();
}

void LedDriver_TurnOff(int ledNumber)
{
	if(IsLedOutOfBounds(ledNumber))
	{
		RUNTIME_ERROR("LED Driver: out-of-bound LED", ledNumber);
		return;
	}

	clearLedImageBit(ledNumber);
	updateHardware();
}

void LedDriver_TurnAllOn(void)
{
	ledsImage = ALL_LEDS_ON;
	updateHardware();
}

