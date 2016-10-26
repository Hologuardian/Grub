#ifndef GRUB_CLOCK_H
#define GRUB_CLOCK_H

#include <Windows.h>

/**
* The Clock class provides access to the high-resolution timer on the
* platform.  By encapsulating the high-resolution timer in a class like
* this, we isolate the rest of the game engine from differences in the
* underlying platform.  The Clock class is a singleton and is typically
* created at the start of the game.
* @author R. N. Robson
*/
class Clock
{
private:
	static LARGE_INTEGER	counter;
	static LARGE_INTEGER	ticksPerSecond;
	static bool				highResolutionSupported;

	/**
	* Private constructor to ensure class is singleton.
	*/
	Clock()
	{
	}

	static inline LARGE_INTEGER getHardwareCounterValue()
	{
		LARGE_INTEGER v;
		QueryPerformanceCounter(&v);
		return v;
	}

public:

	/**
	* Iniatilizaition code to get the frequency of the hardware counter
	* and the initial value of the counter when the clock is created.
	* This MUST be called before the Clock can be used.
	*/
	static void init();

	/**
	* Convert clock ticks to fractional seconds.  Use only for small
	* time durations.
	* @param ticks time in clock ticks
	* @returns time in fractional seconds
	*/
	static inline double ticksToSeconds(LARGE_INTEGER ticks)
	{
		return ((double)ticks.QuadPart) / ((double)ticksPerSecond.QuadPart);
	}

	/**
	* Convert fractional seconds to  clock ticks.
	* @param secs time in clock seconds
	* @returns time in clock ticks
	*/
	static inline LARGE_INTEGER secondsToTicks(double secs)
	{
		LARGE_INTEGER result;
		result.QuadPart = (LONGLONG)(secs * ((double)ticksPerSecond.QuadPart));
		return result;
	}

	/**
	* This returns the number of clock ticks since the Clock was initialized.
	* @returns Clock ticks since clok was created.
	*/
	static inline LARGE_INTEGER getCurrentTicks()
	{
		LARGE_INTEGER result;
		result.QuadPart = /*counter.QuadPart -*/ getHardwareCounterValue().QuadPart;
		return result;
	}

	/**
	* Returns the Clock resolution in ticks per second.
	* @returns The number of clock ticks per second.
	*/
	static inline LARGE_INTEGER getResolution()
	{
		return ticksPerSecond;
	}

	/**
	* This returns the time in seconds since the clock was created.
	* @returns Seconds since clock was created.
	*/
	static inline double getCurrentTime()
	{
		return ticksToSeconds(getCurrentTicks());
	}

	/**
	* This determines if the high-resolution timer was initialized correctly
	* and is ready for use.
	* @returns True if the hardware supports a high-resolution timer.
	*/
	static inline bool isReady()
	{
		return highResolutionSupported;
	}
};

#endif