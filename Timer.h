#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>
#include <SDL.h>

class Timer
{
    public:
        //Initializes variables
        Timer();

        //The various clock actions
        void start();
        void stop();
        void pause();
        void unpause();

        //Gets the timer's time
        unsigned int getTicks();

        //Checks the status of the timer
        bool isStarted();
        bool isPaused();

    private:
        //The clock time when the timer started
        uint32_t startTicks;

        //The ticks stored when the timer was paused
        uint32_t pausedTicks;

        //The timer status
        bool paused;
        bool started;
};

#endif // TIMER_H
