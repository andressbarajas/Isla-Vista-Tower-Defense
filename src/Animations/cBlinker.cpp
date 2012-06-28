
#include "../../include/cSpriteObj.h"
#include "../../include/Animations/cBlinker.h"

void Blinker::nextFrame(SpriteObj *t) {
	++m_frame_cnt;

	if( m_frame_cnt >= m_frames ) {
        if( t->getAlpha() == 0.0f ) {
            t->setAlpha(1.0f);
        }
        else {
            t->setAlpha(0.0f);
        }
        m_frame_cnt = 0;
    }
}
