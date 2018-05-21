#include "Timer.h"

#include <iostream>


Timer::Timer()
    :   _raii   {false}
{
}


Timer::Timer(conststr& name)
    :   _raii   {true}
    ,   _name   {name}
{
    start(_name);
}


Timer::~Timer()
{
    if(_raii) stop();
}


void Timer::start(conststr& name)
{
    _start = hr_clock::now();
}


void Timer::stop()
{
    _end = hr_clock::now();

    auto duration = std::chrono::duration_cast<millisec>(_end - _start).count();
    std::cout << _name << " finished in " << duration << " ms\n";
}

// ================================================================================================================ //

std::string GlobalTimer::_name = "[GB] Section";

hr_clock::time_point GlobalTimer::_start;
hr_clock::time_point GlobalTimer::_end;


void GlobalTimer::start()
{
    _start = hr_clock::now();
}


void GlobalTimer::stop()
{
    _end = hr_clock::now();

    auto duration = std::chrono::duration_cast<millisec>(_end - _start).count();
    std::cout << _name << " finished in " << duration << " ms\n";
}