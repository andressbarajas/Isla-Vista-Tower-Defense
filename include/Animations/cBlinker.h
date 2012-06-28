
#ifndef _ANIMS_BLINKER_H
#define _ANIMS_BLINKER_H

#include "cAnimation.h"

/**
* Class: Blinker
* Blinker inherits Animation so that polymorphism may be used.
* Purpose: To change the transparency of a SpriteObj to a value(0 or 1) depending
* on the amount of frames that have passed.
*/
class Blinker : public Animation {
public:

    /**
    * Constructor
    * Sets m_fade_to to a value specified by the user.  Assigns value of 0 to
    * m_frame_cnt.
    * Pre-conditions: None
    * Post-conditions: The value frames is assigned to m_frames. The value 0 is
    * assigned to m_frame_cnt.
    */
	Blinker(float frames) : m_frames(frames), m_frame_cnt(0) {}
	virtual ~Blinker() {}

	/**
    * Function: nextFrame
    * Sets m_fade_to and m_delta to a value specified by the user.
    * Pre-conditions: None
    * Post-conditions: The alpha component of the SpriteObj is changed 0 or 1
    * after every 'm_frames' frames.
    */
	virtual void nextFrame(SpriteObj *t);

private:
	float	m_frames, m_frame_cnt;
};

#endif	/*_ANIMS_BLINKER_H */
