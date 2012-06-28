

#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_

#include "../cGenMenu.h"
#include "../Drawables/cBanner.h"

class Tutorial : public GenMenu {
public:
	virtual ~Tutorial() { Cleanup(); }

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
    * Function: GetInstance
    * Is used to get the only instance of the tutorial class.
    * Pre-conditions: None
    * Post-conditions: The only instance of Tutorial class is returned.
    */
	static Tutorial* GetInstance() {
	    static Tutorial m_genmenu;
        return &m_genmenu;
    }

protected:

    /**
    * The following constructors are used to help prevent additional creations of the
    * title class.
    */
    Tutorial();                          // Private constructor
    Tutorial(const Tutorial&);              // Prevent copy-construction
    Tutorial& operator= (const Tutorial&);  // Prevent assignment

private:

    Banner m_instructions;
    sf::Image m_ins_img;

};
#endif



