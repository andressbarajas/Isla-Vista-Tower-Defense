
#include "../../include/Popups/cPause.h"

Pause::Pause() {
    m_image.LoadFromFile("media/Sprites/pause.png");
    m_banner.SetImage(m_image);
    setPauseMPosition(sf::Vector2f(350.0f,200.0f));
}

void Pause::Draw(Application &App) {
    App.Draw(*this);
    m_banner.Draw(App);
}

bool Pause::handleEvent(const sf::Input &Input) {
    if(Input.IsKeyDown(sf::Key::Return)) {
        setFinished();
    }
    return true;
}

void Pause::setPauseMPosition(sf::Vector2f pos) {
    SetPosition(pos);
    m_banner.SetPosition(pos);
}

