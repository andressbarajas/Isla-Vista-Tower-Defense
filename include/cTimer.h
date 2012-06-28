

#ifndef _GAME_TIMER_H_
#define _GAME_TIMER_H_

#include <SFML/Window.hpp>

class Timer : public sf::Clock {

public:
    //Initializes variables
    Timer();
    ~Timer() {}

    //The various clock actions
    void start();
    void stop();
    void pause();
    void unpause();
    void update();

    //Gets the timer's time
    long double get_time();

    //Checks the status of the timer
    inline bool is_started() { return m_started; }
    inline bool is_paused() { return m_paused; }

private:
    //The clock time when the timer started
    long double m_start_time;

    //The ticks stored when the timer was paused
    long double m_paused_time;

    //The timer status
    bool m_paused;
    bool m_started;
};

#endif /* _GAME_TIMER_H_ */
