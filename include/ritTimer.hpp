/**
 * @file ritTimer.hpp
 * @author Ritchiel Rez
 * @brief 
 * @version 1.0
 * 
 * @mainpage Ritchiel's timer Library Documentation
 * A std::chrono based library to count elapsed time between specific time points.
 */

#ifndef RIT_TIMER_HPP_INCLUDED
#include <chrono>
#include <ratio>

/// @brief rit namespace used to call methods related to this library
namespace rit
{
using Chrono = std::chrono::high_resolution_clock;
using ChronoTime = Chrono::time_point;

/// @brief milli and sec are std::ratio types which are used to define precision of the elapsed time
using milli = std::milli;
using sec = std::ratio<1>;

/// @brief Timer class to create a timer to count time
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
/// @brief Constructor to start the timer
Timer::Timer()
{
    start();
}

/// @brief Start the timer
void Timer::start()
{
    mStartTime = Chrono::now();
    mPause = false;
    mRunning = true;
}

/// @brief Stop the timer
void Timer::stop()
{
    mEndTime = Chrono::now();
    mPause = true;
    mRunning = false;
}

/// @brief Get the elapsed time
/// @tparam Duration specify precision with std::ratio types
/// @return duration converted to double
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

/// @brief Pause the timer
void Timer::pause()
{
    if (mRunning && !mPause)
    {
        mPause = true;
        mPausedTime = ChronoTime(Chrono::now() - mStartTime);
    }
}

/// @brief Unpause the timer
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
