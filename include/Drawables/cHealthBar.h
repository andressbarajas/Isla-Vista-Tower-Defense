#ifndef _HEALTHBAR_H_
#define _HEALTHBAR_H_

#include "../cSpriteObj.h"

#include <iostream>
#include <SFML/Graphics.hpp>

class HealthBar : public SpriteObj {
public:
    HealthBar();

    ~HealthBar() {}

    void setMaxHealth(float health) { m_max_health = health; }

    int getMaxHealth() { return m_max_health; }

    // Set the amount of health
    void setHealth(int health) { m_current_health = health; }

    // Return the amount of health
    int getHealth() { return m_current_health; }

    // Decrease the amount of health
    void decHealth(int dechealth);

    // Returns true if health is zero; Returns false otherwise
    bool isZero();

    // Draw the health bar
    virtual void Draw(Application &App);

    // Set the health bar width
    void setBarWidth(unsigned int bar_width) { m_bar_width = bar_width; }

    // Set the health bar height
    void setBarHeight(unsigned int bar_height) { m_bar_height = bar_height; }

    // Sets the position of the health bar
    void setBarPosition(const float x, const float y) { Rect.SetPosition(x,y); }

    // Changes the health bars color as it gets low
    virtual void nextFrame();

    // Needed to override because what we are drawing is a private member of this class
    virtual void moveObjects(const float x, const float y) { Rect.Move(x,y); }

private:
    // Represents the health bar
    sf::Shape Rect;

    // Represents the health bar color
    sf::Color m_bar_color;

    // The initial maximum health an object is given
    float m_max_health;

    // Health bars width and height
    float m_bar_width;
    float m_bar_height;

    int m_current_health;
};

#endif /* _HEALTHBAR_H_ */
