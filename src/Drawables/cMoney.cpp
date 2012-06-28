
#include "../../include/Drawables/cMoney.h"

Money::Money() {
    SetCount(0);
    m_string.SetFont(sf::Font::GetDefaultFont());
    m_string.SetSize(20.f);
}

void Money::Draw(Application &App) {
	std::stringstream ss_getInt;

    ss_getInt << GetCount();
    ss_getInt >> m_amount;

    // Remove comment if you dont have a background
    //App.Clear(sf::Color::Blue);

    m_string.SetText(m_amount);
    m_string.SetPosition(GetPosition());
    m_string.SetColor(GetColor());
    //m_string.SetRotation(GetRotation());

	App.Draw(m_string);

	SpriteObj::subDraw(App);
}

