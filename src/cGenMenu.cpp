
#include "../include/cGenMenu.h"
#include "../include/cGamePlay.h"
#include "../include/cApplication.h"

GenMenu::GenMenu() {
    /*
    m_totime = 0.0f;
    m_timeout = 0.0f;
    m_postDelay = 0.0f;
    m_exit = false;
    m_exitCount = m_exitSpeed = 0.0f;
    m_timed_out = false;

    m_bg_color = sf::Color::Black;
    */
    InitDefaults();
}

void GenMenu::InitDefaults() {
    m_totime = 0.0f;
    m_timeout = 0.0f;
    m_postDelay = 0.0f;
    m_exit = false;
    m_exitCount = m_exitSpeed = 0.0f;
    m_timed_out = false;

    m_bg_color = sf::Color::Black;
}

GenMenu::~GenMenu() {
    Cleanup();
}

void GenMenu::Cleanup() { }

void GenMenu::DoState() {

    ResetTimeout();
    m_exit = false;

    while(!m_exit) {
		GetEvents();
		Display();
	}

	// Ok, we're exiting -- do the same as before, but we'll exit out
	// entirely when the scene is finished (and music faded).
	while (!m_gui.isFinished() && m_exitCount > 0.0f) {
		m_exitCount -= m_exitSpeed;
		if (m_exitCount < 0.0f) {
			m_exitCount = 0.0f;
		}
		Display();
	}

	// Did we get a quit-now request?
	if (!m_exitSpeed)
		return;

    // We should be faded out now -- do three more frames to finish
	// clearing out the PVR buffered scenes.
	m_exitCount = 0;

	if (m_postDelay) {
        sf::Sleep(m_postDelay);
	}
}

void GenMenu::GetEvents() {

    Application &App = Application::GetInstance();
    sf::Event Event;

    while(App.GetEvent(Event))
    {
        // Window closed (By clicking on the big red X on the top right of the window)
        if (Event.Type == sf::Event::Closed) {
            App.Close();
            m_exit = true;
        }
    }

    // If m_timeout > 0, which means its value was changed, then ...
    if(m_timeout) {
        m_totime = m_clock.GetElapsedTime();
        if(m_totime > m_timeout) {
            m_timed_out = true;
        }
    }

    GetInput();
}

// This function is meant to be overwritten
/*void GenMenu::GetInput() {

    Application &App = Application::GetInstance();
    const sf::Input& Input = App.GetInput();

    if(Input.IsKeyDown(sf::Key::Right)) {
        cout << "Right Arrow Key Pressed\n\n";
    }
    if(Input.IsKeyDown(sf::Key::Left)) {
        cout << "Left Arrow Key Pressed\n\n";
    }
    if(Input.IsKeyDown(sf::Key::Up)) {
        cout << "Up Arrow Key Pressed\n\n";
    }
    if(Input.IsKeyDown(sf::Key::Down)) {
        cout << "Down Arrow Key Pressed\n\n";
    }
    if(Input.IsKeyDown(sf::Key::Escape)) {
        App.Close();
        m_exit = true;
        return;
    }
    if(m_timed_out) {
        App.Close();
        m_exit = true;
        return;
    }
}*/

void GenMenu::Display() {
    Application &App = Application::GetInstance();

    // Clear the screen
    App.Clear(m_bg_color);

    // Draw stuff here
    m_gui.Draw(App);

    // Display window contents on screen
    App.Display();

    // Advance to the next frame
    m_gui.nextFrame();
}

void GenMenu::StartExit() {
	m_exit = true;
	m_exitCount = 1.0f;
	m_exitSpeed = 1.0f/60.0f;
}

void GenMenu::QuitNow() {
	m_exit = true;
	m_exitCount = 0.0f;
	m_exitSpeed = 0.0f;
}

void GenMenu::ResetTimeout() {
    m_clock.Reset();
}

void GenMenu::SetTimeout(float v) {
    m_timeout = v;
}

void GenMenu::SetBg(sf::Color bgc) {
    m_bg_color = bgc;
}

void GenMenu::SetPostDelay(float s) {
    m_postDelay = s;
}
