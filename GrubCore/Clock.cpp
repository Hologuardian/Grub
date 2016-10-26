#include "Clock.h"

LARGE_INTEGER	Clock::counter;
LARGE_INTEGER	Clock::ticksPerSecond;
bool			Clock::highResolutionSupported = false;

void Clock::init()
{
	highResolutionSupported = QueryPerformanceFrequency(&ticksPerSecond);
	counter = getHardwareCounterValue();
}