#ifndef _ANIMS_LOGXYMOVER_H_
#define _ANIMS_LOGXYMOVER_H_

#include "cAnimation.h"

#include <math.h>
#include <SFML/System/Vector2.hpp>

/**
* Class: LogXYMover
* LogXYMover inherits Animation so that polymorphism may be used.
* Purpose: To change the position [logarithmically] of a SpriteObj to a
* coordinate(x/y plane) specified by the user.
*/
class LogXYMover : public Animation {
public:

    /**
    * Constructor
    * Sets m_dstx and m_dsty to a value specified by the user.
    * Pre-conditions: None
    * Post-conditions: The value dstx and dsty are assigned to
    * m_dstx and m_dsty.
    */
	LogXYMover(float dstx, float dsty) : m_dstx(dstx), m_dsty(dsty) {}
	virtual ~LogXYMover() {}

    /**
    * Function: nextFrame
    * Changes the position of a SpriteObj to a specific coordinate (m_dstx, m_dsty) logarithmically.
    * Pre-conditions: None
    * Post-conditions: Moves the position of a Sprite to the coordinate(m_dstx, m_dsty) 1/8 the
    * distance everytime this function is called.
    */
	virtual void nextFrame(SpriteObj *t);

private:
	float	m_dstx, m_dsty;
};

#endif	/* _ANIMS_LOGXYMOVER_H_ */
