
#include "../../include/Triggers/cTrigger.h"
#include "../../include/Animations/cAnimation.h"

void Trigger::trigger(SpriteObj *t, Animation *a) {
	// Autoclean ourselves once we've triggered
	a->triggerRemove(this);
}
