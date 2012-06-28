
#include "../../include/Popups/cQuit.h"

QuitGame::QuitGame() {
    m_image.LoadFromFile("media/Sprites/quit.png");
    m_banner.SetImage(m_image);
    setPauseMPosition(sf::Vector2f(350.0f,200.0f));
    m_panel = NULL;
}

void QuitGame::Draw(Application &App) {
    App.Draw(*this);
    m_banner.Draw(App);
}

bool QuitGame::handleEvent(const sf::Input &Input) {
    if(Input.IsKeyDown(sf::Key::Y)) {
        setFinished();
        if(m_panel != NULL) {
            m_panel->setQuit();
        }
    }
    if(Input.IsKeyDown(sf::Key::N)) {
        setFinished();
    }
    return true;
}

void QuitGame::setPauseMPosition(sf::Vector2f pos) {
    SetPosition(pos);
    m_banner.SetPosition(pos);
}


