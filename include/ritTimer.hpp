#ifndef RIT_TIMER_HPP_INCLUDED
#include <chrono>
#include <ratio>

namespace rit
{

using Chrono = std::chrono::high_resolution_clock;
using ChronoTime = Chrono::time_point;

using milli = std::milli;
using sec = std::ratio<1>;

class Timer
{
  public:
    Timer();
    void start();
    void stop();
    template <typename Duration> double getTicks();

    void pause();
    void unPause();

  private:
    bool mRunning = false;
    bool mPause = true;

    ChronoTime mStartTime, mEndTime, mPausedTime;
    double mTimeDuration;
};

}; // namespace rit

#define RIT_TIMER_HPP_INCLUDED
#endif // RIT_TIMER_HPP_INCLUDED

#ifdef RIT_TIMER_IMPLEMENTATION

namespace rit
{

Timer::Timer()
{
    start();
}

void Timer::start()
{
    mStartTime = Chrono::now();
    mPause = false;
    mRunning = true;
}

void Timer::stop()
{
    mEndTime = Chrono::now();
    mPause = true;
    mRunning = false;
}

template <typename Duration> double Timer::getTicks()
{
    if (mRunning)
    {
        mTimeDuration =
            std::chrono::duration_cast<std::chrono::duration<double, Duration>>(Chrono::now() - mStartTime).count();
        return mTimeDuration;
    }

    mTimeDuration = std::chrono::duration_cast<std::chrono::duration<double, Duration>>(mEndTime - mStartTime).count();
    return mTimeDuration;
}

void Timer::pause()
{
    if (mRunning && !mPause)
    {
        mPause = true;
        mPausedTime = ChronoTime(Chrono::now() - mStartTime);
    }
}

void Timer::unPause()
{
    if (mRunning && mPause)
    {
        mPause = false;
        mStartTime = ChronoTime(Chrono::now() - mPausedTime);
    }
}

}; // namespace rit

#endif // RIT_TIMER_IMPLEMENTATION
