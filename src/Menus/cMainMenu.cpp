
#include <iostream>

#include "../../include/Menus/cMainMenu.h"
#include "../../include/Menus/cTitle.h"
#include "../../include/Menus/cTutorial.h"
#include "../../include/cLevelGen.h"

using namespace std;

MainMenu::MainMenu() {

    BasicButton *temp = NULL;

    for(int i = 0; i < 4; i++) {
        m_log_move[i] = NULL;
    }


    if (!m_bg_music.OpenFromFile("media/Title/exorcist.ogg"))
    {
    // Error...
    }
    if (!m_snd_buffer.LoadFromFile("media/Title/evillaugh.wav"))
    {
    // Error...
    }

    // New Game Button
    m_btn_img[0].LoadFromFile("media/MainMenu/newgamebutton.png");
    m_btn_img[0].CreateMaskFromColor(sf::Color(255,0,255,255),0);
    m_btn_img[0].SetSmooth(false);

    temp = new BasicButton();
    temp->SetImage(m_btn_img[0]);
    temp->setState(LevelGen::GetInstance());
    m_buttons.push_back(temp);

    // Load Game Button
    m_btn_img[1].LoadFromFile("media/MainMenu/loadgamebutton.png");
    m_btn_img[1].CreateMaskFromColor(sf::Color(255,0,255,255),0);
    m_btn_img[1].SetSmooth(false);

    temp = new BasicButton();
    temp->SetImage(m_btn_img[1]);
    temp->setDisabled(true);
    m_buttons.push_back(temp);

    // Credits Button
    m_btn_img[2].LoadFromFile("media/MainMenu/creditsbutton.png");
    m_btn_img[2].CreateMaskFromColor(sf::Color(255,0,255,255),0);
    m_btn_img[2].SetSmooth(false);

    temp = new BasicButton();
    temp->SetImage(m_btn_img[2]);
    temp->setDisabled(true);
    m_buttons.push_back(temp);

    // Tutorial Button
    m_btn_img[3].LoadFromFile("media/MainMenu/tutorialbutton.png");
    m_btn_img[3].CreateMaskFromColor(sf::Color(255,0,255,255),0);
    m_btn_img[3].SetSmooth(false);

    temp = new BasicButton();
    temp->SetImage(m_btn_img[3]);
    temp->setState(Tutorial::GetInstance());
    m_buttons.push_back(temp);

    m_log_move[0] = new LogXYMover(350.0f, 100.0f);
    m_log_move[1] = new LogXYMover(350.0f, 180.0f);
    m_log_move[2] = new LogXYMover(350.0f, 260.0f);
    m_log_move[3] = new LogXYMover(350.0f, 340.0f);

    Init();
}

MainMenu::~MainMenu() {

    Cleanup();

    if(m_log_move[0] != NULL) {
        delete m_log_move[0];
    }
    if(m_log_move[1] != NULL) {
        delete m_log_move[1];
    }
    if(m_log_move[2] != NULL) {
        delete m_log_move[2];
    }
    if(m_log_move[3] != NULL) {
        delete m_log_move[3];
    }
}

void MainMenu::Init() {
    vector<BasicButton*>::iterator it_buttons;

    InitDefaults();

    SetBg(sf::Color::Red);

    SetTimeout(25.0f);

    m_sound.SetBuffer(m_snd_buffer);

    m_buttons.at(0)->SetPosition(sf::Vector2f(-200.0f, 100.0f));
    m_buttons.at(0)->animAdd(m_log_move[0]);

    m_buttons.at(1)->SetPosition(sf::Vector2f(1260.0f, 180.0f));
    m_buttons.at(1)->animAdd(m_log_move[1]);

    m_buttons.at(2)->SetPosition(sf::Vector2f(-200.0f, 260.0f));
    m_buttons.at(2)->animAdd(m_log_move[2]);

    m_buttons.at(3)->SetPosition(sf::Vector2f(1260.0f, 340.0f));
    m_buttons.at(3)->animAdd(m_log_move[3]);

    for(it_buttons = m_buttons.begin(); it_buttons != m_buttons.end(); it_buttons++) {
        m_gui.subAdd((*it_buttons));
    }

    //m_bg_music.Play();
}

void MainMenu::Cleanup() {
    vector<BasicButton*>::iterator it_buttons;

    for(it_buttons = m_buttons.begin(); it_buttons != m_buttons.end(); it_buttons++) {
        (*it_buttons)->animRemoveAll();
    }

    m_gui.subRemoveAll();

}

void MainMenu::GetInput() {

    Application &App = Application::GetInstance();

    const sf::Input& Input = App.GetInput();

    if(Input.IsKeyDown(sf::Key::Escape)) {
        App.Close();
        StartExit();
        return;
    }
    if(m_timed_out) {
        PopState();
        StartExit();
        return;
    }

    m_gui.handleEvent(Input);

    vector<BasicButton*>::iterator it_buttons;

    for(it_buttons = m_buttons.begin(); it_buttons != m_buttons.end(); it_buttons++){

        if((*it_buttons)->isPressed()){
            PushState((*it_buttons)->getState());
            StartExit();
            return;
        }
    }
}
