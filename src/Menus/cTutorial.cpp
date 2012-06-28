

#include "../../include/cLevelGen.h"
#include "../../include/Menus/cTutorial.h"

Tutorial::Tutorial() {

    m_ins_img.LoadFromFile("media/Tutorial/tutorial.png");
    m_ins_img.CreateMaskFromColor(sf::Color(255,0,255,255),0);
    m_ins_img.SetSmooth(false);

    m_instructions.SetImage(m_ins_img);
}

void Tutorial::Init() {
    InitDefaults();

    SetBg(sf::Color::Blue);

    m_instructions.SetPosition(0,0);

    m_gui.subAdd(&m_instructions);
}

void Tutorial::Cleanup() {
    m_gui.subRemoveAll();
}

void Tutorial::GetInput() {

    Application &App = Application::GetInstance();

    const sf::Input& Input = App.GetInput();

    if(Input.IsKeyDown(sf::Key::Space)) {
        PopState();
        StartExit();
    }
    if(Input.IsKeyDown(sf::Key::Escape)) {
        App.Close();
        m_exit = true;
        return;
    }
}
