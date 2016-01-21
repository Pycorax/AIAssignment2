#ifndef _TIMER_H
#define _TIMER_H

#include <windows.h>

class StopWatch
{
 
 private:
     
    LARGE_INTEGER frequency;
    LARGE_INTEGER prevTime, currTime;
    double LIToSecs( LARGE_INTEGER & L) ;
    UINT     wTimerRes;

 public:
     StopWatch() ;
     ~StopWatch();
     void startTimer();
     double getElapsedTime(); // get time in seconds since the last call to this function
     void waitUntil(long long time);  // wait until this time in milliseconds has passed
	 bool hasTimePassed(double time);  // Check if time since last call exceeded time provided. If it has, return true and reset timer
 };


#endif // _TIMER_H