
#ifndef _TOWERMENU_H_
#define _TOWERMENU_H_

#include <vector>
#include <string>
#include <sstream>
#include "../cApplication.h"
#include "cPanelInterface.h"
#include "cDescriptionPanel.h"
#include "../Drawables/cMoney.h"
#include "../Towers/cTower.h"
#include "../cPlayer.h"
#include <ctime>

class TowerButton;

/*
   Inherits PanelInterface class and holds the buttons that correspond to different towers that
   can be built. Also contains variables of class Money and class DescriptionalPanel so they can
   interact with the vector of buttons.
*/
class TowerPanel : public PanelInterface {
public:
    /**
    * Constructor
    * ***Currently Empty***
    * Pre-conditions: nothing.
    * Post-conditions: initializes TowerPanel members.
    */
    TowerPanel();
    virtual ~TowerPanel() {}

    void Init();
    /**
    * Function: Draw
    * Draws panel onto the Application Window
    * Pre-conditions: There is an existing application window
    * Post-conditions: This panel was drawn onto the application window.
    */
    virtual void Draw(Application &App);
    /**
    * Function: handleEvent
    * function handles input events that may occur inside the panel.
    * **CURRENTLY EMPTY**
    * Pre-conditions: An event has occured.
    * Post-conditions: The event was handled.
    */
    virtual bool handleEvent(const sf::Input& Input);
    /**
    * Functin: moveObjects
    * moves child objects. see SpriteObj for more details.
    * ***CURRENTLY EMPTY***
    * Pre-conditions: nothing.
    * Post-conditions: Moves childeren with the panel.
    */
    virtual void moveObjects(const float x, const float y);

    virtual void nextFrame();

    void setTowerPanelPosition(sf::Vector2f pos);

    inline void setSelectedTower(Tower *sel) { m_selected_tower = sel; }

private:
    sf::Image m_background;
    sf::Image m_button_image[5];
    Money m_money;                      //keeps track of player money
    DescriptionPanel m_desc_panel;
    vector<TowerButton*> m_buttons;
    Tower *m_selected_tower;
    bool m_button_pressed[5];
    clock_t m_press_guard;
};

#endif
