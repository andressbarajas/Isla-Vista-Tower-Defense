
#ifndef _GENMENU_H_
#define _GENMENU_H_

#include <SFML/Graphics.hpp>

#include "Drawables/cScene.h"
#include "cGameStateBase.h"

/**
* Class: GenMenu
* This class handles everything that has to do with logic regarding game states.
* Purpose: To control all the logic that has to do with taking in input and display images
* for the main menu screen.
*/
class GenMenu : public GameStateBase {
public:

    /**
    * Constructor
    * Pre-conditions: None
    * Post-conditions: A GameStateObject is created.
    */
    GenMenu();
    virtual ~GenMenu();

    /**
    * Function: Init
    * Initiates the genmenu variables.  Likely to contain image loading and object creation( using new ).
    * Pre-conditions: None
    * Post-conditions: Depends on the user.
    */
    virtual void InitDefaults();

    /**
    * Function: CleanUp
    * Deallocates any allocated memory.
    * Pre-conditions: None
    * Post-conditions: Depends on user.
    */
    virtual void Cleanup();

    /**
    * Function: DoState
    * Does the genmenu
    * Pre-conditions: None
    * Post-conditions: Depends on user.
    */
    virtual void DoState();

    /**
    * Function: GetEvents
    * Receives input events from the user.
    * Pre-conditions: None
    * Post-conditions: Depends on user.
    */
    virtual void GetEvents();

    /**
    * Function: GetInput
    * Receives input events from the user. Should automatically handle window closer and escape button.
    * Pre-conditions: None
    * Post-conditions: Depends on user.
    */
    virtual void GetInput()=0;

    /**
    * Function: Display
    * Displays the genmenu.
    * Pre-conditions: None
    * Post-conditions: Depends on user.
    */
    virtual void Display();

    /**
    * Function: StartExit
    * Gives the user ability to configure how the genmenu exits
    * Pre-conditions: None
    * Post-conditions: Depends on user.
    */
    virtual void StartExit();

    /**
    * Function: QuitNow
    * Automatically quits the menu.
    * Pre-conditions: None
    * Post-conditions: Depends on user.
    */
    virtual void QuitNow();

    /**
    * Function: ResetTimeout
    * Resets the timer variable that is used for timing out.
    * Pre-conditions: None
    * Post-conditions: m_clock clock is reset.
    */
    virtual void ResetTimeout();

    /**
    * Function: SetTimeout
    * Changes the m_timeout variable to a value specified by the user.
    * Pre-conditions: None
    * Post-conditions: m_timeout is set to value 'v'.
    */
    virtual void SetTimeout(float v);

    /**
    * Function: SetBg
    * Changes the background color of the menu to a color specified by the user.
    * Pre-conditions: None
    * Post-conditions: m_bg_color is set to value 'bgc'.
    */
    virtual void SetBg(sf::Color bgc);

    /**
    * Function: SetPostDelay
    * Sets how long you want the wait time to be when the menu exits
    * Pre-conditions: None
    * Post-conditions: m_postDelay is set to value 's'.
    */
	void SetPostDelay(float s);

protected:
    float m_totime;    // When was last time user did something?
    float m_timeout;   // How many seconds before trigger a time out?
    float m_postDelay; // Post-DoState delay in case sounds are still playing
    float m_exitCount;
	float m_exitSpeed;

    bool m_exit;       // Bool running variable
    bool m_timed_out;  // Timed out?

    sf::Clock m_clock;
    sf::Color m_bg_color;

    Scene  m_gui;
};

#endif /* _GENMENU_H_ */
