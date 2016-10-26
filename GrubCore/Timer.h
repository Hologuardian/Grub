#ifndef GRUB_TIMER_H
#define GRUB_TIMER_H

#include "Clock.h"

/**
* The Timer class is used to represent a time line in a game.  The Clock
* class provides access to the global time line for the game.  The Clock
* class does not allow for scaling or alteration of time -- it is simply
* an interface to the underlying hardware timer.  A Timer has its time
* updated manually and can be scaled to run at a different speed than the
* global time line.  A timer can be paused so that any updates to the time
* of a paused timer will have no effect on the timer.  The Timer uses the
* Clock class for some calculations, so the Clock class must have been
* initialized before the Timer is used.
* @author R. N. Robson
*/
class Timer
{
private:
	LARGE_INTEGER		counter;
	double				scaleFactor;
	bool				paused;

public:
	/**
	* Construct a new timer set to zero.  It has a scale factor of 1.0
	* and is running.
	*/
	Timer() : scaleFactor(1.0), paused(false)
	{
		counter.QuadPart = 0L;
	}

	/**
	* Either pause or start the timer.
	* @param p If true the timer is paused.
	*/
	inline void setPaused(bool p)
	{
		paused = p;
	}

	/**
	* Determine if the timer is paused.
	* @returns True if the timer is paused.
	*/
	inline bool isPaused()
	{
		return paused;
	}

	/**
	* Set the scale factor for the timer.  Default is 1.0.
	* @param s The factor to scale time by.
	*/
	inline void setScale(double s)
	{
		scaleFactor = s;
	}

	/**
	* Determine the scale factor for the timer
	* @returns The scale factor.
	*/
	inline double getScale()
	{
		return scaleFactor;
	}

	/**
	* Update the Timer by adding the indicated number of clock ticks.
	* @param ticks Positive or negative number of ticks.
	*/
	void updateTicks(LARGE_INTEGER ticks);

	/**
	* Update the Timer by adding the indicated number of seconds.
	* @param secs Positive or negative number of seconds.
	*/
	void updateSeconds(double secs);

	/**
	* Set the Timer to an absolute number of ticks.  This has no
	* effect if the Timer is paused.
	* @param ticks The new tick value for the Timer.
	*/
	void set(LARGE_INTEGER ticks);

	/**
	* Return the value for this timer in ticks.
	* @returns The number of ticks on this counter.
	*/
	inline LARGE_INTEGER getTicks() const
	{
		return counter;
	}

	/**
	* Return the value for this timer in seconds.
	* @returns The number of seconds on this counter.
	*/
	double getSeconds() const;

	/**
	* Calculate the time difference between two timers in seconds.
	* This might be more accurate than getting seconds from a timer
	* directly since the difference might be small, and hence, more precise.
	* @ returns The number of seconds when subtracting other from this.
	*/
	double calculateDelta(Timer& other);

};

#endif