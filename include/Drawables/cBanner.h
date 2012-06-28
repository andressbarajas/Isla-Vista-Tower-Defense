#ifndef _BANNER_H_
#define _BANNER_H_

#include "../cSpriteObj.h"
#include "../cApplication.h"

/**
* Class: Banner
* This class adds acts like the sf::Sprite class. Sub drawables can be attached to this
* drawable.
* Purpose: To act like the sf::Sprite class which only displays an image and not take
* any input.
*/
class Banner : public SpriteObj {
public:

    Banner() {}
    /**
    * Constructor
    * Sets the image for the banner.
    * Pre-conditions: None
    * Post-conditions: The image variable of Banner is set equal to 'image'.
    */
	Banner(sf::Image &image);
	virtual ~Banner() {}

    /**
    * Function: Draw
    * Takes the Application window (App) as a parameter to know which window to draw into.
    * Pre-conditions: None
    * Post-conditions: The banner image is drawn on the screen.
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
    * Moves the object(Banner) and any objects attached(sub drawables) with it.
    * Pre-conditions: None
    * Post-conditions: Banner and its sub drawables are moved 'x' units in the x-direction and 'y' in the y-direction.
    */
    virtual void moveObjects(const float x, const float y);

private:

};

#endif	/* _BANNER_H_ */
