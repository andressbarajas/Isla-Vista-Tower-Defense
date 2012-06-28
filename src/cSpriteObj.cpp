
#include "../include/cSpriteObj.h"

SpriteObj::SpriteObj() {

    m_parent = NULL;
	m_finished = false;
	m_subs_finished = false;
}

SpriteObj::~SpriteObj() { }

void SpriteObj::animAdd(Animation *a) {
    /* Add at the back of the list */
    m_anims.push_back(a);
}

void SpriteObj::animRemove(Animation *r) {
    /* Remove element r from the list */
    m_anims.remove(r);
}

void SpriteObj::animRemoveAll() {
    /* Delete all animations */
    m_anims.clear();
}

bool SpriteObj::isFinished() {

    if(m_subs_finished) {
        return m_finished;
    }

    list<SpriteObj*>::iterator it;
    for(it = m_subs.begin(); it != m_subs.end(); it++ ) {
         if(!(*it)->isFinished()) {
             return false;
         }
    }

    m_subs_finished = true;
	return m_finished;
}

void SpriteObj::setFinished() {
    m_finished = true;

	list<SpriteObj*>::iterator it;
    for(it = m_subs.begin(); it != m_subs.end(); it++ ) {
         (*it)->setFinished();
    }

}

void SpriteObj::subDraw(Application &App) {

    list<SpriteObj*>::iterator it;
    for(it = m_subs.begin(); it != m_subs.end(); it++) {
        if (!(*it)->isFinished()) {
            (*it)->Draw(App);
        }
    }
}

void SpriteObj::subNextFrame(){

    list<SpriteObj*>::iterator it, it2;
    for(it = m_subs.begin(); it != m_subs.end(); ) {
        it2 = ++it;
        --it;
        if (!(*it)->isFinished() && (*it) != NULL) {
            (*it)->nextFrame();
        }
        it = it2;
    }
}

void SpriteObj::subAdd(SpriteObj *t) {

    //assert( t->m_parent == NULL );
	t->m_parent = this;
	t->moveObjects( GetPosition().x, GetPosition().y );
	m_subs.push_back(t);
}

void SpriteObj::subRemove(SpriteObj *t) {

    //assert( t->m_parent == this );
	t->m_parent = NULL;
    m_subs.remove(t);
}

void SpriteObj::subRemoveFinished() {

	list<SpriteObj*>::iterator it, it2;

	for(it = m_subs.begin(); it != m_subs.end();  ) {
        it2 = ++it;
        --it;
        if((*it)->isFinished()) {
            //assert( (*it)->m_parent == this );
            (*it)->m_parent = NULL;
            m_subs.erase(it);
            if(*it != NULL) {
                delete *it;
            }
        }
        it = it2;
    }
}

void SpriteObj::subRemoveAll() {

	list<SpriteObj*>::iterator it;

    for(it = m_subs.begin(); it != m_subs.end(); it++ ) {
        // assert( (*t)->m_parent == this );
        (*it)->m_parent = NULL;
    }
    m_subs.clear();
}

void SpriteObj::nextFrame() {

	list<Animation*>::iterator it, it2;
	for(it = m_anims.begin(); it != m_anims.end(); ) {
        // We do getNext() first here in case an animation
		// decides to remove itself from the list.
		it2 = ++it;
		--it;
		(*it)->nextFrame(this);
        it = it2;
    }

    subNextFrame();
}

void SpriteObj::setAlpha(const float& a) {
    sf::Color color = GetColor();
    color.a = (uint8)(a*255);
    SetColor(color);
}

float SpriteObj::getAlpha() const {
    sf::Color color = GetColor();
    return (float)(color.a/255.0f);
}

void SpriteObj::moveSubs(const float x, const float y) {

    list<SpriteObj*>::iterator it;

    for(it = m_subs.begin(); it != m_subs.end(); it++ ) {

        (*it)->moveObjects(x, y);
    }
}

bool SpriteObj::handleSubEvents(const sf::Input& Input) {

    list<SpriteObj*>::iterator it;

    for(it = m_subs.begin(); it != m_subs.end(); it++ ) {
        (*it)->handleEvent(Input);
    }

    return true;
}

void SpriteObj::moveObjects(const float x, const float y) {
    Move(x, y);
    moveSubs(x, y);
}
