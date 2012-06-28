
#ifndef _BUTTON_H_
#define _BUTTON_H_

#include "../cSpriteObj.h"
#include "../cApplication.h"

/**
* Class: Button
* Button provides an abstract class that handles all the basic functions of a
* button.
* Purpose: To inherited by other buttons so that polymorphism can be used.
*/
class Button : public SpriteObj {
public:

    /**
    * Constructor
    * Sets m_pressed, m_highlighted, and m_disabled to a default boolean value.
    * Pre-conditions: None
    * Post-conditions: m_pressed, m_highlighted, and m_disabled are set to false.
    */
    Button() : m_pressed(false), m_highlighted(false), m_disabled(false) {}
	virtual ~Button() {}

	/**
    * Function: Draw
    * Takes the Application window (App) as a parameter to know which window to draw into.
    * Pre-conditions: None
    * Post-conditions: The button image is drawn on the screen.
    */
	virtual void Draw(Application &App);

	/**
    * Function: handleEvent
    * Takes input from the mouse and the keyboard as a parameter.
    * Pre-conditions: None
    * Post-conditions: Changes the boolean values of m_pressed and m_highlighted depending
    * on the mouse input.
    */
	virtual bool handleEvent(const sf::Input &Input);

	/**
    * Function: moveObjects
    * Moves the object(Button) and any objects attached(sub drawables) to it.
    * Pre-conditions: None
    * Post-conditions: Button and its sub drawables are moved 'x' units in the x-direction and 'y' in the y-direction.
    */
    virtual void moveObjects(const float x, const float y);

    //virtual void nextFrame() {}

    /**
    * Function: isPressed
    * Returns the boolean value of m_pressed.
    * Pre-conditions: None
    * Post-conditions: Returns m_pressed.
    */
    bool isPressed() { return m_pressed; }

    /**
    * Function: isHighlighted
    * Returns the boolean value of m_highlighted.
    * Pre-conditions: None
    * Post-conditions: Returns m_highlighted.
    */
    bool isHighlighted() { return m_highlighted; }

    /**
    * Function: buttonEvent
    * Is a pure virtual function. It provides the user with the functionality to assign operations
    * to the button when it is highlighted, pressed, or disabled.
    * Pre-conditions: None
    * Post-conditions: Depends on user.
    */
    virtual void buttonEvent()=0;

    /**
    * Function: setDisabled
    * Sets 'm_disabled' to a boolean value given by the user.
    * Pre-conditions: None
    * Post-conditions: Sets 'm_disabled' equal to boolean variable 'disable'.
    */
    void setDisabled(bool disable) { m_disabled = disable; }

    /**
    * Function: getDisabled
    * Returns the boolean value of m_disabled.
    * Pre-conditions: None
    * Post-conditions: Returns m_disabled.
    */
    bool getDisabled() { return m_disabled; }

    //void setButtonImage(sf::Image *button_img) { m_button_img = *button_img; }

private:
    bool m_pressed;
    bool m_highlighted;
    bool m_disabled;
    bool m_already_pressed;

protected:

};

#endif
