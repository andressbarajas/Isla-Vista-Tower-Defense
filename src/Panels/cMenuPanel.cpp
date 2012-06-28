
#include "../../include/Buttons/cMenuButton.h"
#include "../../include/Panels/cMenuPanel.h"

#include "../../include/Popups/cPause.h"
#include "../../include/Popups/cQuit.h"

MenuPanel::MenuPanel() {

    Init();

    m_button_imgs[0].LoadFromFile("media/Sprites/pausebutton.png");
    m_button_imgs[0].CreateMaskFromColor(sf::Color(255,0,255,255),0);
    m_button_imgs[0].SetSmooth(false);

    m_button_imgs[1].LoadFromFile("media/Sprites/quitbutton.png");
    m_button_imgs[1].CreateMaskFromColor(sf::Color(255,0,255,255),0);
    m_button_imgs[1].SetSmooth(false);


    // when constructing each button you also give it a spriteobj popup to each
    MenuButton * temp = new MenuButton();
    temp->setMenu(new Pause());
    temp->SetImage(m_button_imgs[0]);

    m_buttons.push_back(temp);

    temp = new MenuButton();
    temp->setMenu(new QuitGame());
    temp->setPanel(this);
    temp->SetImage(m_button_imgs[1]);

    m_buttons.push_back(temp);

    // create buttons (setting location, image, etc)
    // subAdd all the buttons
    m_background.LoadFromFile("media/Sprites/menupanelbg.png");
    SetImage(m_background);

    // create buttons (setting location, image, etc)
    // subAdd all the buttons
}

void MenuPanel::Init() {
     m_menu = NULL;
     m_quit = false;
}

void MenuPanel::Draw(Application &App) {

    vector<MenuButton*>::iterator it_buttons;

    // Draw the Tower Panel background
    App.Draw(*this);

    // Draw Buttons
    for(it_buttons = m_buttons.begin(); it_buttons != m_buttons.end(); it_buttons++) {
        (*it_buttons)->Draw(App);
    }
}

bool MenuPanel::handleEvent(const sf::Input& Input) {
    vector<MenuButton*>::iterator it_buttons;
    for(it_buttons = m_buttons.begin(); it_buttons != m_buttons.end(); it_buttons++) {
        (*it_buttons)->handleEvent(Input);
    }
    return true;
}

void MenuPanel::moveObjects(const float x, const float y) {

}

void MenuPanel::nextFrame() {

    vector<MenuButton*>::iterator it_buttons;

    // Iterate through all the buttons to set their tint value if they are disabled or
    // to get their description if highlighted
    for(it_buttons = m_buttons.begin(); it_buttons != m_buttons.end(); it_buttons++) {

        //(*it_buttons)->nextFrame();

        // If a button is highlighted and we aren't already displaying the status of a
        // tower(since it has precedence) have the description panel get the description
        // of the tower button to display.
        if((*it_buttons)->isPressed()) {
            m_menu = (*it_buttons)->getMenu();
        }
    }
}

Popup* MenuPanel::getMenu() {
    if(m_menu == NULL) {
        return NULL;
    }
    if(m_menu->isFinished()) {
        m_menu->notFinished();
        m_menu = NULL;
        return NULL;
    }

    return m_menu;
}

void MenuPanel::setMenuPanelPosition(sf::Vector2f pos) {
    SetPosition(pos);

    m_buttons.at(0)->SetPosition(pos.x+50.0f, pos.y+10.0f);
    m_buttons.at(1)->SetPosition(pos.x+180.0f, pos.y+10.0f);
}
