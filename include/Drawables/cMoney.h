
#ifndef _MONEY_H_
#define _MONEY_H_

#include "../tCounter.h"
#include "../cSpriteObj.h"
#include "../cApplication.h"

#include <sstream>
#include <iostream>
#include <SFML/Graphics/String.hpp>

/**
* Class: Money
* Money class inherits the Counter and SpriteObj class.
* Purpose: To display the player's money and to keep track of the money.
*/
class Money : public Counter<long double>, public SpriteObj {
public:

    /**
    * Constructor
    * Sets m_count(protected variable of class Counter) to zero and sets the default size and font for
    * 'm_string'.
    * Pre-conditions: None
    * Post-conditions: m_count is set to 0, the size of the font is set to 20 and the default font provided
    * by SFML is used.
    */
    Money();
    ~Money() {}

    /**
    * Function: SetFont
    * Sets the font to be used to display the amount of money.  Takes the user specified font.
    * Pre-conditions: None
    * Post-conditions: Font used is set equal to 'font'.
    */
    void SetFont(const sf::Font &font)  { m_string.SetFont(font); }

    /**
    * Function: SetSize
    * Takes a float parameter equal to the size the user wants for the font.
    * Pre-conditions: None
    * Post-conditions: The size of the font is set to 'size'.
    */
    void SetSize(const float size) { m_string.SetSize(size); }

    /**
    * Function: Draw
    * Takes the Application window (App) as a parameter to know which window to draw into.
    * Pre-conditions: None
    * Post-conditions: The 'm_string' variable is drawn on the screen.
    */
    virtual void Draw(Application &App);

    /**
    * Function: handleEvent
    * Takes input from the mouse and the keyboard as a parameter.  Doesn't do anything with
    * the parameter.
    * Pre-conditions: None
    * Post-conditions: Returns true.
    */
	virtual bool handleEvent(const sf::Input &Input) { return true; }

	/**
    * Function: moveObjects
    * Moves the object(Money) and any objects attached(sub drawables) to it.
    * Pre-conditions: None
    * Post-conditions: Money and its sub drawables are moved 'x' units in the x-direction and 'y' in the y-direction.
    */
    virtual void moveObjects(const float x, const float y) {}

private:
    sf::String m_string;
    std::string m_amount;
};

#endif
