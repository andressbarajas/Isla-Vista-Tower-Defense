#ifndef _ANIMS_EXPXYMOVER_H_
#define _ANIMS_EXPXYMOVER_H_

#include "cAnimation.h"

#include <SFML/System/Vector2.hpp>

/**
* Class: ExpXYMover
* ExpXYMover inherits Animation so that polymorphism may be used.
* Purpose: To change the position [exponentially] of a SpriteObj to a
* coordinate(x/y plane) specified by the user.
*/
class ExpXYMover : public Animation {
public:

    /**
    * Constructor
    * Sets m_dx, m_dy, m_maxx, and m_maxy to a value specified by the user.
    * Pre-conditions: None
    * Post-conditions: The value dx, dy, maxx, and maxy are assigned to
    * m_dx, m_dy, m_maxx, and m_maxy.
    */
	ExpXYMover(float dx, float dy, float maxx, float maxy) : m_dx(dx), m_dy(dy), m_maxx(maxx), m_maxy(maxy) {}
	virtual ~ExpXYMover() {}

    /**
    * Function: nextFrame
    * Changes the position of a SpriteObj to the coordinate (m_maxx, m_maxy) exponentially.
    * Pre-conditions: None
    * Post-conditions: Moves the position of a Sprite to the coordinate(m_maxx, m_maxy) 1.15f times the
    * distance everytime this function is called.
    */
	virtual void nextFrame(SpriteObj *t);

private:
	float	m_dx, m_dy, m_maxx, m_maxy;
};

#endif	/* _ANIMS_EXPXYMOVER_H_ */
