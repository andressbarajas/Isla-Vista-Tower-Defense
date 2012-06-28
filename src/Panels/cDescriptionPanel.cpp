
#include "../../include/Panels/cDescriptionPanel.h"

DescriptionPanel::DescriptionPanel() {
    // create buttons (setting location, image, etc)
    // subAdd all the buttons
    m_background.LoadFromFile("media/Sprites/descpanelbg.png");
    SetImage(m_background);

    m_header.SetFont(sf::Font::GetDefaultFont());
    m_header.SetSize(15.f);
    m_header.SetColor(sf::Color::Black);
    m_header.SetText("Description");

    m_description.SetFont(sf::Font::GetDefaultFont());
    m_description.SetSize(15.f);
    m_description.SetColor(sf::Color::Black);
    m_description.SetText("Select a tower to upgrade it!\nNeed cups for parties!\n");
}

void DescriptionPanel::Draw(Application &App) {
    App.Draw(*this);

    // Or you can add the following through subAdd() function
    App.Draw(m_header);
    App.Draw(m_description);

    subDraw(App);
}

void DescriptionPanel::moveObjects(const float x, const float y) {

}

void DescriptionPanel::nextFrame() {

    //m_header.SetText(temp);
    //m_description.SetText(temp2);

}

void DescriptionPanel::setDescPanelPosition(sf::Vector2f pos) {
    SetPosition(pos);
    m_header.SetPosition(pos.x+10.0f, pos.y+10.0f);
    m_description.SetPosition(pos.x+20.0f, pos.y+m_header.GetFont().GetCharacterSize()+10.f);
}

void DescriptionPanel::setHeader(char *header) {
    m_header.SetText(header);
}

void DescriptionPanel::setDescription(string description) {
    m_description.SetText(description);
}

