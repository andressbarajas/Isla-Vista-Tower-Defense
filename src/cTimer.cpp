
#include "../include/cTimer.h"

Timer::Timer() {

    m_start_time = 0.0;
    m_paused_time = 0.0;
    m_paused = false;
    m_started = false;
}

void Timer::start() {

    // Start the timer
    m_started = true;

    // Unpause the timer
    m_paused = false;

    // Get the current clock time
    m_start_time = GetElapsedTime();
}

void Timer::stop() {

    // Stop the timer
    m_started = false;

    // Unpause the timer
    m_paused = false;
}

void Timer::pause() {

    // If the timer is running and isn't already paused
    if((m_started == true) && (m_paused == false))
    {
        // Pause the timer
        m_paused = true;

        // Calculate the paused time
        m_paused_time = GetElapsedTime() - m_start_time;
    }
}

void Timer::unpause() {

    // If the timer is paused
    if( m_paused == true )
    {
        // Unpause the timer
        m_paused = false;

        // Reset the starting time
        m_start_time = GetElapsedTime() - m_paused_time;

        // Reset the paused time
        m_paused_time = 0.0;
    }
}

long double Timer::get_time() {

    // If the timer is running
    if(m_started == true) {

       //If the timer is paused
        if( m_paused == true )
        {
            // Return the number of seconds when the timer was paused
            return m_paused_time;
        }
        else
        {
            // Return the current time minus the start time
            return (GetElapsedTime() - m_start_time);
        }
    }

    // If the timer isn't running
    return 0;
}
