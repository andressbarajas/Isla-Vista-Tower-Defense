
#ifndef _ANIMS_ALPHAFADER_H_
#define _ANIMS_ALPHAFADER_H_

#include "cAnimation.h"

/**
* Class: AlphaFader
* Alpha inherits Animation so that polymorphism may be used.
* Purpose: To change the transparency of a SpriteObj to a value specified by the
* user.
*/
class AlphaFader : public Animation {
public:

    /**
    * Constructor
    * Sets m_fade_to and m_delta to a value specified by the user.
    * Pre-conditions: None
    * Post-conditions: The value fade_to is assigned to m_fade_to. The value delta
    * is assigned to m_delta.
    */
	AlphaFader(float fade_to, float delta) : m_fade_to(fade_to), m_delta(delta) {}
	virtual ~AlphaFader() {}


    /**
    * Function: nextFrame
    * Changes the transparency of a SpriteObj to a specific value (m_fade_to) incrementally
    * by a value(m_delta).
    * Pre-conditions: None
    * Post-conditions: The alpha component of the SpriteObj is changed by a value m_delta.
    */
	virtual void nextFrame(SpriteObj *t);

private:
	float	m_fade_to, m_delta;
};

#endif	/* _ANIMS_ALPHAFADER_H_ */
