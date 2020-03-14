#include "DumbExample.h"

int8_t AverageThreeBytes(int8_t a, int8_t b, int8_t c)
{
	return (int8_t)(((int16_t)a + (int16_t)b + (int16_t)c) / 3);
}

uint8_t SumNumb(uint8_t first, uint8_t second)
{
	return (first+second);
}

