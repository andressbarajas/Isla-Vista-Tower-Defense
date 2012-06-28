
#ifndef _SCENE_H_
#define _SCENE_H_

#include "../cSpriteObj.h"

/**
* Class: Scene
* Purpose: Acts as a sort of gui class that holds all the other things that will be drawn on the
* screen.  It is used to organize drawing and input functions in other classes.
*
*/
class Scene : public SpriteObj {
public:

    /**
    * Constructor
    * Pre-conditions: None
    * Post-conditions: Is set as finished so that its subdrawables can be drawn when a 'Scene'
    * variable is told to be drawn.  The same goes for the input.
    */
	Scene() {
		// Scene is always finished itself, because it doesn't draw
		// anything. This will make it check its sub-drawables for
		// finishedness before acquiescing.
		setFinished();
	}
	virtual ~Scene() {}

	/**
    * Function: Draw
    * Takes the Application window (App) as a parameter to know which window to draw into.
    * Pre-conditions: None
    * Post-conditions: The sub drawables of this SpriteObj are drawn.
    */
	virtual void Draw(Application &App);

	/**
    * Function: handleEvent
    * Takes input from the mouse and the keyboard as a parameter.
    * Pre-conditions: None
    * Post-conditions: Sends the input to its sub drawables
    */
	virtual bool handleEvent(const sf::Input &Input);

	/**
    * Function: moveObjects
    * Moves the object(Scene) and any objects attached(sub drawables) to it.
    * Pre-conditions: None
    * Post-conditions: Scene and its sub drawables are moved 'x' units in the x-direction and 'y' in the y-direction.
    */
    virtual void moveObjects(const float x, const float y);
};

#endif	/* _SCENE_H_ */

