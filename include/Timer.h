#pragma once
#ifndef TIMER_H
#define TIMER_H

#include "BaseObject.h"
#include "Def.h"

class Timer
{
private:
    int ticks_start;
    int ticks_pause;

    bool isPaused;
    bool isStarted;
public:
    Timer(/* args */);
    ~Timer();

    int GetTicks();

    bool CheckStarted();
    bool CheckPause();

    void Start();
    void Stop();
    void Pause();
    void Continue();

};




#endif // TIMER_H