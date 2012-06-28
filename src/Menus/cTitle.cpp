
#include "../../include/Menus/cTitle.h"
#include "../../include/cLevelGen.h"
#include "../../include/Menus/cMainMenu.h"

Title::Title() {

     /* Load  All Media Files */
    if (!m_title_img.LoadFromFile("media/sidewalk.jpg"))
    {
    // Error...
    }
    if (!m_press_enter_img.LoadFromFile("media/Title/press_enter.png"))
    {
    // Error...
    }
    if (!m_bg_music.OpenFromFile("media/Title/exorcist.ogg"))
    {
    // Error...
    }
    if (!m_snd_buffer.LoadFromFile("media/Title/evillaugh.wav"))
    {
    // Error...
    }

    m_press_enter_img.CreateMaskFromColor(sf::Color(255,0,255,255),0);
    m_press_enter_img.SetSmooth(false);

    /* Create SpriteObj with the images we just loaded */
    m_title = new Banner(m_title_img);
    m_press_enter = new Banner(m_press_enter_img);

    m_blinker = new Blinker(35.0f);

}

void Title::Init() {
    InitDefaults();

    SetBg(sf::Color::Black);

    m_sound.SetBuffer(m_snd_buffer);

    /* Setup the title banner */
    m_title->SetPosition(20,0);

    /* Setup the press enter banner */
    m_press_enter->SetPosition(340,420);
    m_press_enter->animAdd(&*m_blinker);

    /* Add them to main drawable */
    m_gui.subAdd(&*m_title);
    m_gui.subAdd(&*m_press_enter);

    m_bg_music.Play();
}

void Title::Cleanup() {
    m_press_enter->animRemoveAll();
    m_gui.subRemoveAll();
}

void Title::GetInput() {

    Application &App = Application::GetInstance();

    const sf::Input& Input = App.GetInput();

    if(Input.IsKeyDown(sf::Key::Return)) {
        PushState(MainMenu::GetInstance());
        m_sound.Play();
        StartExit();
    }
    if(Input.IsKeyDown(sf::Key::Escape)) {
        App.Close();
        m_exit = true;
        return;
    }
}

void Title::StartExit() {
    //m_press_enter->animRemoveAll();
    GenMenu::StartExit();
    m_bg_music.Stop();
}
