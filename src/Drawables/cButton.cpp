
#include "../../include/Drawables/cButton.h"

void Button::Draw(Application &App) {
	App.Draw(*this);
	subDraw(App);
}

bool Button::handleEvent(const sf::Input &Input) {
    bool leftMouseDown = Input.IsMouseButtonDown(sf::Mouse::Left);
    unsigned int mouseX = Input.GetMouseX();
    unsigned int mouseY = Input.GetMouseY();

    if( mouseX >= GetPosition().x && mouseY >= GetPosition().y &&
        mouseX <= (GetPosition().x + GetImage()->GetWidth()) && mouseY <= (GetPosition().y + GetImage()->GetHeight()) ) {

        m_highlighted = true;

        if(leftMouseDown && !m_disabled) {
            m_pressed = true;
           // m_already_pressed = true;
        }
        else{
            //m_already_pressed = false;
            m_pressed = false;
        }

    } else {
        m_pressed = false;
        m_highlighted = false;
    }

    buttonEvent();

    return true;
}

void Button::moveObjects(const float x, const float y) {
    Move(x, y);
    moveSubs(x, y);
}

