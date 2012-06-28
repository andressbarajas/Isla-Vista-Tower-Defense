
#ifndef _MENUMAIN_H_
#define _MENUMAIN_H_

#include "../cGenMenu.h"
#include "../Drawables/cBanner.h"
#include "../Animations/cLogXYMover.h"
#include "../Animations/cExpXYMover.h"

#include "../Panels/cMapPanel.h"
#include "../Panels/cMenuPanel.h"
#include "../Panels/cTowerPanel.h"

#include "../Buttons/cBasicButton.h"


#include <SFML/Audio.hpp>

/**
* Class: MainMenu
* This class handles everything that has to do with the main menu screen of IVTD
* Purpose: To control all the logic that has to do with taking in input and display images
* for the main menu screen.
*/
class MainMenu : public GenMenu {
public:
	virtual ~MainMenu();

    /**
    * Function: Init
    * Initiates the main menu defaults and loads all the media files that will be used for the title screen
    * Pre-conditions: None
    * Post-conditions: All image, sound, music files are loaded into memory. Panels are added to the gui variable
    * 'm_gui'.
    */
	virtual void Init();

	virtual void Cleanup();

    /**
    * Function: GetInput
    * Gives the user the ability to set up operations that will take place when a certain input from
    * the keyboard or mouse is entered.
    * Pre-conditions: None
    * Post-conditions: The operation assignment for an input that takes place is executed.
    */
    virtual void GetInput();

    /**
    * Function: GetInstance
    * Is used to get the only instance of the MainMenu class.
    * Pre-conditions: None
    * Post-conditions: The only instance of MainMenu class is returned.
    */
	static MainMenu* GetInstance() {
	    static MainMenu m_genmenu;
        return &m_genmenu;
    }

protected:
    /**
    * The following constructors are used to help prevent additional creations of the
    * MainMenu class.
    */
    MainMenu();                             // Private constructor
    MainMenu(const MainMenu&);              // Prevent copy-construction
    MainMenu& operator= (const MainMenu&);  // Prevent assignment

private:

    vector<BasicButton*> m_buttons;
    sf::Image m_btn_img[4];

    sf::Sound m_sound;
    sf::Music m_bg_music;
    sf::SoundBuffer m_snd_buffer;

    LogXYMover * m_log_move[4];

    sf::String m_description;
};


#endif /* _MENUMAIN_H_ */

