
#ifndef _TITLE_H_
#define _TITLE_H_

#include "../cGenMenu.h"
#include "../copied_ptr.h"
#include "../Drawables/cBanner.h"
#include "../Animations/cBlinker.h"

#include <SFML/Audio.hpp>

/**
* Class: Title
* This class handles everything that has to do with the title screen of IVTD
* Purpose: To control all the logic that has to do with taking in input and display images
* for the title screen.
*/

class Title : public GenMenu {
public:
	virtual ~Title() { Cleanup(); }

    /**
    * Function: Init
    * Initiates title menu defaults and loads all the media files that will be used for the title screen
    * Pre-conditions: None
    * Post-conditions: All image, sound, music files are loaded into memory.
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
    * Function: StartExit
    * Configures how the title screen will exit.
    * Pre-conditions: None
    * Post-conditions: The title screen exits.
    */
    virtual void StartExit();

    /**
    * Function: GetInstance
    * Is used to get the only instance of the title class.
    * Pre-conditions: None
    * Post-conditions: The only instance of Title class is returned.
    */
	static Title* GetInstance() {
	    static Title m_genmenu;
        return &m_genmenu;
    }

protected:

    /**
    * The following constructors are used to help prevent additional creations of the
    * title class.
    */
    Title();                          // Private constructor
    Title(const Title&);              // Prevent copy-construction
    Title& operator= (const Title&);  // Prevent assignment

private:

    copied_ptr<Banner> m_title;
    copied_ptr<Blinker> m_blinker;
    copied_ptr<Banner> m_press_enter;

    sf::Image m_title_img;
    sf::Image m_press_enter_img;

    sf::Sound m_sound;
    sf::Music m_bg_music;
    sf::SoundBuffer m_snd_buffer;
};
#endif


