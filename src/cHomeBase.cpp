
#include "../include/cHomeBase.h"

HomeBase::HomeBase() {
    m_base_img.LoadFromFile("media/Sprites/freebirds.png");
    m_base_img.CreateMaskFromColor(sf::Color(255,0,255,255),0);
    m_base_img.SetSmooth(false);
    SetImage(m_base_img);

    m_health.setBarWidth(120);
    m_health.setBarHeight(15);

}

void HomeBase::setBaseHealthPosition(sf::Vector2f pos) {
    m_health.setBarPosition(pos.x,pos.y);
}

void HomeBase::Draw(Application &App) {
     App.Draw(*this);

     m_health.Draw(App);
}

void HomeBase::nextFrame() {
    m_health.nextFrame();
}
