#ifndef _ANIMATION_H_
#define _ANIMATION_H_

#include <list>
#include "../Triggers/cTrigger.h"

using namespace std;

class SpriteObj;

class Animation {
public:
	// Constructor / Destructor
	Animation();
	virtual ~Animation();

	// Add a trigger to our list of triggers
	void triggerAdd(Trigger *t);

	// Remove a trigger from our list of triggers
	void triggerRemove(Trigger *t);

	// Remove all triggers from our list of triggers
	void triggerRemoveAll();

	// Move to the next frame of animation
	virtual void nextFrame(SpriteObj *t);

protected:
	// Trigger any triggers
	virtual void trigger(SpriteObj *t);

	// Call when the animation has completed
	virtual void complete(SpriteObj *t);

private:
	list<Trigger*>	m_triggers;		// Animation triggers
};

#endif	/* _ANIMATION_H_ */
