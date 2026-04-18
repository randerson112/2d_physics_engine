//Implementation of custom timer class

#include "Timer.hpp"

Timer::Timer(float interval) : m_interval(interval), m_currentTime(0) {}

void Timer::step(float time)
{
    m_currentTime += time;
}

bool Timer::timeout()
{
    if (m_currentTime >= m_interval)
        return true;
    return false;
}

void Timer::reset()
{
    m_currentTime = 0;
}