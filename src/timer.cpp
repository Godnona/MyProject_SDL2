#include "Timer.h"

Timer::Timer(/* args */)
{
    ticks_start = 0;
    ticks_pause = 0;
    isPaused = false;
    isStarted = false;
}

Timer::~Timer()
{
}

/*=============================|Set_Get|=============================*/

int Timer::GetTicks()
{
    if(isStarted == true)
    {
        if(isPaused == true)
        {
            return ticks_pause;
        }
        else 
            return SDL_GetTicks() - ticks_start;
    }
    return 0;
}

bool Timer::CheckStarted()
{
    return isStarted;
}

bool Timer::CheckPause()
{
    return isPaused;
}

/*=============================|Handle|=============================*/

void Timer::Start()
{
    isStarted = true;
    isPaused = false;
    ticks_start = SDL_GetTicks();
}

void Timer::Stop()
{
    isStarted = false;
    isStarted = false;
}

void Timer::Pause()
{
    if(isStarted == true && isPaused == false)
    {
        isPaused = true;
        ticks_pause = SDL_GetTicks() - ticks_start;
    }
}

void Timer::Continue()
{
    if(isPaused == true)
    {
        isPaused = false;
        ticks_start = SDL_GetTicks() - ticks_pause;
        ticks_pause = 0;
    }
}
