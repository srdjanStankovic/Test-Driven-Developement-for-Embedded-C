#include "LedDriver.h"

static uint16_t * ledsAddress;

void LedDriver_Create(uint16_t * address)
{
	ledsAddress = address;
	*address = 0;
}

void LedDriver_Destroy(void)
{

}

void LedDriver_TurnOn(int LedNumber)
{
	*ledsAddress = LedNumber;
}

void LedDriver_TurnOff(int LedNumber)
{
	*ledsAddress = 0;/*LedNumber;*/
}

