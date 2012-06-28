#ifndef _MENUPANEL_H_
#define _MENUPANEL_H_

#include <vector>

#include "../cApplication.h"
#include "cPanelInterface.h"
#include "../Popups/cPopup.h"

class MenuButton;

/*
   Inherits PanelInterface class and holds the buttons that correspond to different towers that
   can be built. Also contains variables of class Money and class DescriptionalPanel so they can
   interact with the vector of buttons.
*/
class MenuPanel : public PanelInterface {
public:
    /**
    * Constructor
    * ***Currently Empty***
    * Pre-conditions: nothing.
    * Post-conditions: initializes MenuPanel members.
    */
    MenuPanel();
    virtual ~MenuPanel() {}

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

    void setMenuPanelPosition(sf::Vector2f pos);

    void setMenu(Popup *menu) { m_menu = menu; }

    Popup* getMenu();

    bool Quit() { return m_quit; }

    void setQuit() { m_quit = true; }

private:
    bool m_quit;
    sf::Image m_background;
    sf::Image m_button_imgs[4];
    Popup *m_menu;
    vector<MenuButton*> m_buttons;
};

#endif

