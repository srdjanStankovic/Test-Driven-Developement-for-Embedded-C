#include "../unity/extras/fixture/src/unity_fixture.h"
#include "../src/LedDriver.h"
#include "../include/util/RuntimeError.h"
#include "../mocks/RuntimeErrorStub.h"

static uint16_t virtualLeds;

TEST_GROUP(LedDriver);

TEST_SETUP(LedDriver)
{
	LedDriver_Create(&virtualLeds);
}

TEST_TEAR_DOWN(LedDriver)
{
}

TEST(LedDriver, LedsOffAfterCreate)
{
	uint16_t virtualLeds = 0xffff;
	LedDriver_Create(&virtualLeds);
	TEST_ASSERT_EQUAL_HEX16(0, virtualLeds);
}

TEST(LedDriver, TurnOnLedOne)
{
	LedDriver_TurnOn(1);
	TEST_ASSERT_EQUAL_HEX16(1, virtualLeds);
}

TEST(LedDriver, TurnOffLedOne)
{
	LedDriver_TurnOn(1);
	LedDriver_TurnOff(1);
	TEST_ASSERT_EQUAL_HEX16(0, virtualLeds);
}

TEST(LedDriver, TurnOnMultipleLeds)
{
	LedDriver_TurnOn(9);
	LedDriver_TurnOn(8);
	TEST_ASSERT_EQUAL_HEX16(0x180, virtualLeds);
}

TEST(LedDriver, TurnOffAnyLed)
{
	/*LedDriver_TurnOn(9);
	LedDriver_TurnOn(8);*/
	LedDriver_TurnAllOn();
	LedDriver_TurnOff(8);
	TEST_ASSERT_EQUAL_HEX16(0xff7f, virtualLeds);
}

TEST(LedDriver, AllOn)
{
	LedDriver_TurnAllOn();
	TEST_ASSERT_EQUAL_HEX16(0xffff, virtualLeds);
}

TEST(LedDriver, LedMemoryIsNotReadable)
{
	virtualLeds = 0xffff;
	LedDriver_TurnOn(8);
	TEST_ASSERT_EQUAL_HEX16(0x80, virtualLeds);
}

TEST(LedDriver, UpperAndLowerBounds)
{
	LedDriver_TurnOn(1);
	LedDriver_TurnOn(16);
	LedDriver_TurnOn(8);
	TEST_ASSERT_EQUAL_HEX16(0x8081, virtualLeds);
}

TEST(LedDriver, OutOfBoundsChangesNothing)
{
	LedDriver_TurnOn(-1);
	LedDriver_TurnOn(0);
	LedDriver_TurnOn(17);
	LedDriver_TurnOn(3141);
	TEST_ASSERT_EQUAL_HEX16(0, virtualLeds);
}

TEST(LedDriver, OutOfBoundsTurnOffDoesNoHarm)
{
	LedDriver_TurnAllOn();

	LedDriver_TurnOff(-1);
	LedDriver_TurnOff(0);
	LedDriver_TurnOff(17);
	LedDriver_TurnOff(3141);
	TEST_ASSERT_EQUAL_HEX16(0xFFFF, virtualLeds);
}

TEST(LedDriver, OutBoundsProducesRuntimeError)
{
	LedDriver_TurnOn(-1);
	TEST_ASSERT_EQUAL_STRING("LED Driver: out-of-bound LED",
			RuntimeErrorStub_GetLastError());
	TEST_ASSERT_EQUAL(-1, RuntimeErrorStub_GetLastParameter());
}

IGNORE_TEST(LedDriver, OutBoundsToDo)
{
	/*TODO: Nothing*/
}
