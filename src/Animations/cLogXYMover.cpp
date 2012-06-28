
#include "../../include/cSpriteObj.h"
#include "../../include/Animations/cLogXYMover.h"

void LogXYMover::nextFrame(SpriteObj *t) {
	sf::Vector2f pos = t->GetPosition();

	if (fabs(pos.x - m_dstx) < 1.0f && fabs(pos.y - m_dsty) < 1.0f) {
		t->SetPosition(sf::Vector2f(m_dstx, m_dsty));
		//complete(t);
		return;
	} else {
		// Move 1/8 of the distance each frame
		float dx = m_dstx - pos.x;
		float dy = m_dsty - pos.y;
		t->SetPosition(sf::Vector2f(pos.x + dx/8.0f, pos.y + dy/8.0f));
	}
}
