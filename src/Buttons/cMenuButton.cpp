
#include "../../include/Buttons/cMenuButton.h"

MenuButton::MenuButton() {
    m_menu = NULL;
}

MenuButton::~MenuButton() {
    if(m_menu != NULL) {
        delete m_menu;
    }
}

void MenuButton::Draw(Application &App) {
    App.Draw(*this);

	subDraw(App);
}

void MenuButton::buttonEvent() {

    //if clicked

    //if highlighted

}

void MenuButton::setPanel(MenuPanel *panel) {
    if(m_menu != NULL) {
        m_menu->setPanel(panel);
    }
}
