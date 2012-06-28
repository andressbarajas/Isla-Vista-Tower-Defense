#ifndef _Level_H_
#define _Level_H_

#include <iostream>
#include <SFML/Audio.hpp>

#include "cApplication.h"
#include "Drawables/cScene.h"
#include "Panels/cMapPanel.h"
#include "Panels/cTowerPanel.h"
#include "Panels/cMenuPanel.h"
#include "Popups/cPopup.h"
#include "cPlayer.h"
#include "cTimer.h"

/**
* Class: Level
* Purpose: Draws the map, panels, towers, and enemies and controls music
*/
class Level {
public:
    /**
    * Constructor
    * Pre-Conditions: none
    * Post-Conditions: Level is drawn
    */
    Level();
    ~Level() { Cleanup(); }

    void Init();

    void Cleanup();

    void Start();

    void Pause();

    void UnPause();

    /**
    * Function: handleEvents
    * Handles events done by the user such as clicking a button
    * Pre-Conditions: event occurs
    * Post-Conditions: event was handled
    */
    void handleEvents(Application &App);

    void nextFrame();

    /**
    * Function: Draw
    * Draws everything on the map
    * Pre-Conditions: none
    * Post-Conditions: Map was drawn
    */
    void Draw(Application &App);
    /**
    * Function: DoLevel
    * function is in control of running the level and determines when to stop
    * Pre-condition: none
    * Post-condition: Round/Level is over
    */
    void DoLevel();
    /**
    * Function: QuitNow
    * function sets m_exit boolean to true
    * Pre-condition: m_exit is false
    * Post-condition: m_exit is true
    */
    void QuitNow() { m_exit = true; }

private:
    Scene m_gui;

    Timer m_time;

    MapPanel m_map_pnl;
    TowerPanel m_tower_pnl;
    MenuPanel m_menu_pnl;

    sf::Music m_bg_music;

    Popup *m_active_menu; // Change to Popup variable pointer *

    bool m_exit;
};

#endif /* _Level_H_ */

