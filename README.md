## Ritchiel's timer library

#### A std::chrono based library to count elapsed time between specific time points.

When I started to make my own game, one thing that I had to do was to count how much time had
past each frame (frame time). Couting the elapsed time can be difficult, because it is hard to
fine a cross-platform highly accurate way to count the elapsed time.

Fortunately, with **modern C++**, you can use the ```std::chrono``` library, which is already avalaible
by default. But still counting the elapsed time can be difficult, because the library is not easy to use.
So I made a timer library based on ```std::chrono```, with some basic features such as:

#### 1. Multiple timers
You can create multiple timer objects, to count the time in different specific points in your program.
Example:
```c++
#define RIT_TIMER_IMPLEMENTATION
#include <ritTimer.hpp>
int main()
{
    rit::Timer timer1;

    for(int i = 1; i <= 1000; ++i)
    {
        std::cout << i << "\n";
    }

    std::cout << "Time elapsed(milliseconds): " << timer1.getTicks<std::milli>() << "\n";
    timer1.stop();

    rit::Timer timer2;

    for(int i = 1; i <= 1000000; ++i)
    {
        std::cout << i << "\n";
    }

    std::cout << "Time elapsed(milliseconds): " << timer2.getTicks<std::milli>() << "\n";
    timer2.stop();
}
```

#### 2. Pause/unpause timers
You can pause then unpause a specific timer if you want so. Example:
```c++
#define RIT_TIMER_IMPLEMENTATION
#include <ritTimer.hpp>
int main()
{
    rit::Timer timer1;

    for(int i = 1; i <= 1000; ++i)
    {
        std::cout << i << "\n";
        if(i == 100)
        {
            timer1.pause();
        }
    }

    timer1.unpause();
    std::cout << "Time elapsed(milliseconds): " << timer1.getTicks<std::milli>() << "\n";
}
```

As you can see from examples, if you want to use the library, in your main source file you need to define
`RIT_TIMER_IMPLEMENTATION` macro. Because this library is header only library, you will just need to copy
the `ritTimer.hpp` to your include directory of your project. This is done for simplicity reasons, as installing
and including **3rd party C++ libraries** can be painful in your projects.

**If you liked the project, do not forget to star it. Also do not forget to open *issues* if you find any and *pull requests* to solve those *issues*.**
