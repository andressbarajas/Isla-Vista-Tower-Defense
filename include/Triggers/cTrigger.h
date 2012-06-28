#ifndef _TRIGGER_H_
#define _TRIGGER_H_

class SpriteObj;
class Animation;

#include <list>

/**
* Class: Trigger
* Trigger provides an abstract class that handles all the basic functions of a
* trigger which are used for animations.
* Purpose: To inherited by other triggers so that polymorphism can be used.
*/
class Trigger {
public:

	/**
    * Constructor
    * Just a regular default constructor. Does nothing.
    * Pre-conditions: None
    * Post-conditions: A trigger is created.
    */
	Trigger() {}
	virtual ~Trigger() {}

	/**
    * Function: trigger
    * Called when we have reached the trigger point in the
    * given animation/drawable
    * Pre-conditions: None
    * Post-conditions: Removes the trigger from the animation/drawable.
    */
	virtual void trigger(SpriteObj *t, Animation *a);
};

#endif	/* _TRIGGER_H_ */
