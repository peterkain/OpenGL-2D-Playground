#pragma once

#include "StringTypes.h"
#include "ChronoTypes.h"

#include <chrono>

class Timer
{
public:
    Timer();

    void start(conststr& name);
    void stop();

    Timer(conststr& name);
    ~Timer();

private:
    bool _raii;
    std::string _name;

    hr_clock::time_point _start;
    hr_clock::time_point _end;
};


class GlobalTimer
{
public:
    GlobalTimer() = delete;

    static void start();
    static void stop();

    static std::string _name;

private:
    static hr_clock::time_point _start;
    static hr_clock::time_point _end;
};
