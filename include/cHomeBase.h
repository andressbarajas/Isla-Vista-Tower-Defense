
#ifndef _HOMEBASE_H_
#define _HOMEBASE_H_

#include "Drawables/cHealthBar.h"
#include "cSpriteObj.h"

class HomeBase : public SpriteObj {
public:
    HomeBase();
    ~HomeBase() {}
    void setHealth(unsigned int hp) { m_health.setHealth(hp); }
    void decHealth(unsigned int dechealth) { m_health.decHealth(dechealth); }
    void setMaxHealth(unsigned int hp) { m_health.setMaxHealth(hp); }
    bool Lose() { return m_health.isZero(); }
    void setBaseHealthPosition(sf::Vector2f pos);
    virtual void Draw(Application &App);
    virtual void nextFrame();

protected:
private:

    HealthBar m_health;
    sf::Image m_base_img;
};

#endif /* _HOMEBASE_H_ */
