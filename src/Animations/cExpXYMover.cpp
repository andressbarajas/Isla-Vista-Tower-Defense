
#include "../../include/cSpriteObj.h"
#include "../../include/Animations/cExpXYMover.h"

void ExpXYMover::nextFrame(SpriteObj *t) {
	sf::Vector2f p = t->GetPosition();

	bool xfin = m_dx < 0 ? (p.x <= m_maxx) : (p.x >= m_maxx);
	bool yfin = m_dy < 0 ? (p.y <= m_maxy) : (p.y >= m_maxy);
	if (xfin && yfin) {
		t->SetPosition(sf::Vector2f(m_maxx, m_maxy));
		//complete(t);
		return;
	}

	// Move 1.15x of the distance each frame
	p += sf::Vector2f(m_dx, m_dy);
	t->SetPosition(p);
	m_dx *= 1.15f;
	m_dy *= 1.15f;
}
