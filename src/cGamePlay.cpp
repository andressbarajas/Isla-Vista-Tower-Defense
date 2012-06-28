
#include "../include/cGamePlay.h"
#include "../include/cGameStateBase.h"

#include "../include/Menus/cTitle.h"

void GamePlay::Init() {

    /* Print a banner */
	cout << "\n<-------------------- Isla Vista Tower Defense START ----------------->\n\n";

	/* Get an instance of the Application class so we can call its functions */
	Application &App = Application::GetInstance();

    /* Create a window and limited the speed of the game to 60 fps */
    App.Create(sf::VideoMode(1060, 580, 32), "Isla Vista Tower Defense");
    App.UseVerticalSync(true);
    App.SetFramerateLimit(60);
}

void GamePlay::Run() {

    Application &App = Application::GetInstance();

    /* Logo */
	//doLogo();

	/* Disclaimer */
	//doDisclaimer();

    /* Start with ... */
    ChangeState(Title::GetInstance());

    while( App.IsOpened() ) {
        DoState();
    }
}

void GamePlay::Shutdown() {

    Application &App = Application::GetInstance();

	/* Cleanup all states on the stack */
	while ( !m_states.empty() ) {
		m_states.back()->Cleanup();
		m_states.pop_back();
	}

    /* Print a closing Banner */
	cout << "\n<------------------- Isla Vista Tower Defense FINISH ----------------->\n\n" ;

    /* Close the Application if it isn't closed already */
	if(App.IsOpened()) {
        Quit();
	}
}

void GamePlay::DoState() {

     if ( !m_states.empty() ) {
		// Let the state(on top of the stack) do it's thing
	    m_states.back()->DoState();
	 } else {
         cout << "GamePlay(DoState): Stack is empty. Cannot DoState with empty stack. \n\nQuiting....\n";
         Quit();
     }

}

void GamePlay::ChangeState(GameStateBase* state)
{
	// Cleanup the current state
	if ( !m_states.empty() ) {
		m_states.back()->Cleanup();
		m_states.pop_back();
	}

	// Store and init the new state
	m_states.push_back(state);
	m_states.back()->Init();
}

void GamePlay::PushState(GameStateBase* state)
{
	// Pause current state
	/*if ( !m_states.empty() ) {
		m_states.back()->Pause();
    }*/

	// Store and init the new state
	m_states.push_back(state);
	m_states.back()->Init();
}

void GamePlay::PopState()
{
	// Cleanup the current state
	if ( !m_states.empty() ) {
		m_states.back()->Cleanup();
		m_states.pop_back();
	}

	// Resume previous state
	/*if ( !m_states.empty() ) {
		m_states.back()->Resume();
	}*/
}

void GamePlay::Quit() {

    /* Close the Appliction Window */
    Application &App = Application::GetInstance();
    App.Close();
}

