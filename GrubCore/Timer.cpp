#include "Timer.h"


void Timer::updateTicks(LARGE_INTEGER ticks)
{
	if (!paused)
	{
		counter.QuadPart += (ticks.QuadPart * scaleFactor);
	}
}

void Timer::updateSeconds(double secs)
{
	if (!paused)
	{
		counter.QuadPart += Clock::secondsToTicks((secs * scaleFactor)).QuadPart;
	}
}

void Timer::set(LARGE_INTEGER ticks)
{
	if (!paused)
	{
		counter = ticks;
	}
}

double Timer::getSeconds() const
{
	return Clock::ticksToSeconds(counter);
}

double Timer::calculateDelta(Timer& other)
{
	LARGE_INTEGER v;
	v.QuadPart = counter.QuadPart - other.counter.QuadPart;
	return Clock::ticksToSeconds(v);
}