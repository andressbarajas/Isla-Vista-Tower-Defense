
#include "../../include/cSpriteObj.h"
#include "../../include/Animations/cAlphaFader.h"

void AlphaFader::nextFrame(SpriteObj *t) {

	sf::Color c = t->GetColor();
	if((c.a+(m_delta*255)) > 255) {
	    c.a = 255;
	    t->SetColor(c);
        complete(t);
        return;
	} else if((c.a+(m_delta*255)) < 0) {
	    c.a = 0;
	    t->SetColor(c);
        complete(t);
        return;
	} else {
	    c.a += (uint8)(m_delta*255);
	}
    t->SetColor(c);

	if (m_delta < 0.0f) {
		if (c.a <= (uint8)(m_fade_to*255)) {
			c.a = (uint8)(m_fade_to*255);
			t->SetColor(c);
			complete(t);
		}
	} else {
		if (c.a >= (uint8)(m_fade_to*255)) {
			c.a = (uint8)(m_fade_to*255);
			t->SetColor(c);
			complete(t);
		}
	}
}
