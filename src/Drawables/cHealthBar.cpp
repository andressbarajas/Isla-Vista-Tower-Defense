
#include "../../include/Drawables/cHealthBar.h"

HealthBar::HealthBar() {
    m_bar_color = sf::Color::Green;
    m_max_health = 0.0f;
    m_bar_width = 0.0f;
    m_bar_height = 0.0f;
    m_current_health = 0;
    //Rect = sf::Shape::Rectangle(0,0, m_bar_width, m_bar_height, m_bar_color);
}

void HealthBar::decHealth(int dechealth) {

    m_current_health -= dechealth;

    if(m_current_health < 0) {
        m_current_health = 0;
    }
}


bool HealthBar::isZero() {
    // If the health is zero return true
    if(m_current_health <= 0.0f) {
        return true;
    }
    // Otherwise return false
    return false;
}

void HealthBar::Draw(Application &App) {

    // No point in drawing a health bar with no health points
    if(m_current_health <= 0.0f) {
        return;
    }

    // Draw the health bar
    App.Draw(Rect);

    // Draw any spriteobjs attached to the health bar
	SpriteObj::subDraw(App);
}

void HealthBar::nextFrame() {

    float ratio;
    sf::Vector2f position = Rect.GetPosition();

    // Ratio to caclulate the width of the health bar
    ratio = (float)(m_current_health/m_max_health);

    // If the health is 65% or greater of the max
    if( ratio >= 0.65 ) {
        // Make the health bar Green
        m_bar_color = sf::Color(0, 255, 0);
    }
    // If the health is greater than 25% and less than 65%
    else if( (ratio >= 0.25) && (ratio < 0.65) ) {
        // Make the health bar Yellow
        m_bar_color = sf::Color(255, 255, 0);
    }
    // If the health is below 25%
    else if( ratio < 0.25f ) {
        // Make the health bar Red
        m_bar_color = sf::Color(255, 0, 0);
    }

    Rect = sf::Shape::Rectangle(0,0, ratio*m_bar_width, m_bar_height, m_bar_color);
    Rect.SetPosition(position);
}

