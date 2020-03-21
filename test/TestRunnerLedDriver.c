#include "../unity/extras/fixture/src/unity_fixture.h"
#include "../include/util/RuntimeError.h"
#include "../mocks/RuntimeErrorStub.h"

TEST_GROUP_RUNNER(LedDriver)
{
	RUN_TEST_CASE(LedDriver, LedsOffAfterCreate);
	RUN_TEST_CASE(LedDriver, TurnOnLedOne);
	RUN_TEST_CASE(LedDriver, TurnOffLedOne);
	RUN_TEST_CASE(LedDriver, TurnOnMultipleLeds);
	RUN_TEST_CASE(LedDriver, TurnOffAnyLed);
	RUN_TEST_CASE(LedDriver, AllOn);
	RUN_TEST_CASE(LedDriver, LedMemoryIsNotReadable);
	RUN_TEST_CASE(LedDriver, UpperAndLowerBounds);
	RUN_TEST_CASE(LedDriver, OutOfBoundsChangesNothing);
	RUN_TEST_CASE(LedDriver, OutOfBoundsTurnOffDoesNoHarm);
	RUN_TEST_CASE(LedDriver, OutBoundsProducesRuntimeError);
	RUN_TEST_CASE(LedDriver, OutBoundsToDo);
}
