
#include "../include/cLevel.h"

Level::Level() {
    Player &player = Player::GetInstance();
    player.setLives(50);
    player.setMoney(100);
    m_active_menu = NULL;

    // Setup the Map Panel
    m_map_pnl.SetMap("media/Level/IV1.fmp");
    m_map_pnl.SetStartPosition(sf::Vector2f (0,50));
    m_map_pnl.moveObjects(0,50);
    m_map_pnl.SetMapDimension(sf::Vector2f(860, 550));
    m_map_pnl.GenerateMapLookUp();

    if (!m_bg_music.OpenFromFile("media/Level/g6.ogg"))
    {
    // Error...
    }

    Init();
}

void Level::Init() {

    Player &player = Player::GetInstance();
    player.setLives(50);
    m_active_menu = NULL;

    m_gui.subAdd(&m_map_pnl);

    // Setup the Tower Panel
    m_tower_pnl.setTowerPanelPosition(sf::Vector2f(860.0f, 0.0f));
    m_gui.subAdd(&m_tower_pnl);

    // Setup the Menu Panel (sets up its own submenus aka pop ups)
    m_menu_pnl.setMenuPanelPosition(sf::Vector2f(0.0f, 0.0f));
    m_gui.subAdd(&m_menu_pnl);

    m_map_pnl.Init();
    m_tower_pnl.Init();
    m_menu_pnl.Init();

    m_bg_music.SetLoop(true);
    m_bg_music.SetVolume(60.0f);
}

void Level::Cleanup() {
    m_gui.subRemoveAll();
    m_bg_music.Stop();
}

void Level::Start() {
    m_time.start();
    m_map_pnl.Start();
}

void Level::Pause() {
    m_time.pause();
    m_map_pnl.Pause();
}

void Level::UnPause() {
    m_time.unpause();
    m_map_pnl.UnPause();
}

void Level::handleEvents(Application &App) {

    const sf::Input& Input = App.GetInput();
    sf::Event Event;

    while(App.GetEvent(Event)) {

        // Window closed (By clicking on the big red X on the top right of the window)
        if (Event.Type == sf::Event::Closed) {
            App.Close();
            m_exit = true;
            return;
        }
    }

    // If escape key is pressed close the window (application).
    if(Input.IsKeyDown(sf::Key::Escape)) {
        App.Close();
        m_exit = true;
        return;
    }

    // If there is NOT(!) an active menu go ahead and take input for the panels
    if(!m_active_menu) {
        m_gui.handleEvent(Input);
    }

    // If there is an active menu, only take input for it
    if(m_active_menu) {
        // Get input for pop up menu
        m_active_menu->handleEvent(Input);
    }
}

void Level::nextFrame() {

    Player &player = Player::GetInstance();

    // Check if the Player Lost
    if (player.getLives() <= 0) {
        m_exit = true;
        return;
    }

    // check if we now have an active menu
    m_active_menu = m_menu_pnl.getMenu();

    if(m_menu_pnl.Quit()) {
       m_exit = true;
       return;
    }

    // If we do NOT(!) have an active menu then continue with panel animations
    if(!m_active_menu) {

        UnPause();

        m_map_pnl.nextFrame();

        m_tower_pnl.setSelectedTower(m_map_pnl.getSelectedTower());
        m_tower_pnl.nextFrame();

        m_menu_pnl.nextFrame();
    }

     // If we DO have an active menu then only continue with the menu
     // animations.
    if(m_active_menu) {
        Pause();
        m_active_menu->nextFrame();
    }
}

void Level::Draw(Application &App) {

    if(m_exit) {
        return;
    }

    // Clear screen
    App.Clear();

    // Draw the panels into the buffer
    m_gui.Draw(App);

    App.Draw(sf::Shape::Rectangle(0, 50.0f, 860.0f, 580.0f, sf::Color(0, 0, 0, 130)));

    // If we have a menu pop up, draw it
    if(m_active_menu) {

        // Tints the background panels using a black transparent rectangle that covers the whole screen
        App.Draw(sf::Shape::Rectangle(0, 0, App.GetWidth(), App.GetHeight(), sf::Color(0, 0, 0, 230)));

        // draw active menu on top of the tinted panels
        m_active_menu->Draw(App);
    }

    // Finally, display the buffered frame on screen
    App.Display();
}

void Level::DoLevel() {

    Application &App = Application::GetInstance();
    m_exit = false;

    m_bg_music.Play();
    Start();

    while(!m_exit) {
		handleEvents(App);
		Draw(App);
		nextFrame();
	}
}


