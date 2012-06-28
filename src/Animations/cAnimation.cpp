
#include "../../include/Animations/cAnimation.h"
#include "../../include/cSpriteObj.h"


Animation::Animation() {
}

Animation::~Animation() {
}

void Animation::triggerAdd(Trigger *t) {
	m_triggers.push_back(t);
}

void Animation::triggerRemove(Trigger *tr) {
	m_triggers.remove(tr);
}

void Animation::triggerRemoveAll() {
	m_triggers.clear();
}

void Animation::nextFrame(SpriteObj *t) {
}


void Animation::trigger(SpriteObj *t) {

	// Call each active trigger
	list<Trigger*>::iterator it, tn;

	for(it = m_triggers.begin(); it != m_triggers.end(); ) {
	    tn = ++it;
	    --it;
	    (*it)->trigger(t, this);
	    it = tn;
	}
}

void Animation::complete(SpriteObj *d) {
	// Call any completion triggers
	trigger(d);

	// Remove us from the parent Drawable
	d->animRemove(this);
}
