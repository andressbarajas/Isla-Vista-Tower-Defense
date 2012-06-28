#ifndef _SPRITEOBJ_H_
#define _SPRITEOBJ_H_

#include "Animations/cAnimation.h"
#include "cApplication.h"

#include <list>
#include <SFML/Window.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <iostream>
using namespace std;

// For Alpha Values
typedef unsigned char uint8;

using namespace std;

class SpriteObj : public sf::Sprite {
public:
    SpriteObj();
    ~SpriteObj();

    // Add an animation object
	void animAdd(Animation * a);

	// Remove an animation object
	void animRemove(Animation * r);

	// Remove all animation objects
	void animRemoveAll();

	// Checks to see if this object is still not finished (for screen
	// closing type stuff). Returns true if this object and all
	// sub-objects are finished.
	bool isFinished();

	// Set this object to be finished
	virtual void setFinished();

	// Move to all sub-drawables to the next frame (if any)
	void subNextFrame();

	// Add a new object to our sub-drawables
	void subAdd(SpriteObj *t);

	// Remove an object from our sub-drawables
	void subRemove(SpriteObj *t);

	// Remove any sub-drawables that are marked finished
	void subRemoveFinished();

	// Remove all objects from our sub-drawables
	void subRemoveAll();

	// Move to the next frame of animation
	virtual void nextFrame();

    // Set the transparency level of the drawable
    void setAlpha(const float& a);

    // Get the transparency level of the drawable
    float getAlpha() const;

    // Draw this drawable: Should be overwritten
	virtual void Draw(Application &App) = 0;

	// Handle the events
	virtual bool handleEvent(const sf::Input &Input) { return true; }

	void notFinished() { m_finished = false; }

    // Move the SpriteObj and its children
    virtual void moveObjects(const float x, const float y);

	SpriteObj   * getParent() const { return m_parent; }

protected:

    void moveSubs(const float x, const float y);
    bool handleSubEvents(const sf::Input& Input);
	void subDraw(Application &App);

	SpriteObj	* m_parent;		// Our parent object

	bool		m_finished;		    // Is it "finished" (i.e., can safely be removed from scene)
	bool		m_subs_finished;

    list<Animation*>  m_anims;	// Animation objects
	list<SpriteObj*>  m_subs;   // Our sub-drawable list

};

#endif /* _SPRITEOBJ_H_ */
