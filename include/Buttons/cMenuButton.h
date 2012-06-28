

#ifndef _MENUBUTTON_H_
#define _MENUBUTTON_H_

#include "../cLevel.h"
#include "../Drawables/cButton.h"
#include "../Popups/cPopup.h"

/**
* Class: MenuButton
* MenuButton inherits Button class so that polymorphism may be used.
* Purpose: To hold the properties of the menu buttons like: Save, Quit,
* Pause, and Load.
*/
class MenuButton : public Button {
public:

    /**
    * Constructor
    * Calls the default Button constructor.
    * Pre-conditions: None
    * Post-conditions: Superclass(Button) protected variables are assigned default values.
    */
    MenuButton();
    virtual ~MenuButton();

    /**
    * Function: Draw
    * Takes the Application window (App) as a parameter to know which window to draw into.
    * Pre-conditions: None
    * Post-conditions: The button image is drawn on the screen
    */
    virtual void Draw(Application &App);

    /**
    * Function: buttonEvent
    * Provides the user with the functionality to assign operations to the button when it is
    * highlighted, pressed, or disabled.
    * Pre-conditions: None
    * Post-conditions: Depends on user.
    */
    virtual void buttonEvent();

    void setMenu(Popup *menu) { m_menu = menu; }

    Popup* getMenu() { return m_menu; }

    void setPanel(MenuPanel *panel);

private:
    Popup *m_menu;
};

#endif /* _MENUBUTTON_H_ */
