#ifndef TIMER_HPP
#define TIMER_HPP

//Custom timer class
//Used for limiting object spawning speed and displaying fps
class Timer
{
public:
    //Constructor to set interval in seconds
    Timer(float interval);

    //Steps timer by specified amount of time
    void step(float time);

    //Returns true if the timer has reached interval
    bool timeout();

    //Resets the timer back to counting from zero
    void reset();

private:
    float m_interval; //The interval in seconds at which the timer times out
    float m_currentTime; //The current time elapsed since last reset
};

#endif