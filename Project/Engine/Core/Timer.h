#ifndef TIMER_H
#define TIMER_H

#include<SDL.h>

constexpr float MILL_TO_SEC = 1000.0f;//magic number??? 
//macro

class Timer
{
public:
	//Copy is perhibited 
	Timer(const Timer&) = delete;
	Timer(Timer&&) = delete;
	Timer& operator=(const Timer&) = delete;
	Timer& operator=(Timer&&) = delete;

	Timer();
	~Timer();
	void Start();
	void UpdateFrameTicks();
	float GetDeltaTime() const;
	unsigned int GetSleepTime(const unsigned int fps_) const;
	float GetCurrentTickMilli() const;//ms
	float GetCurrentTickSec() const;//sec

private:
	unsigned int prevTicks;
	unsigned int currentTicks;
};


#endif

