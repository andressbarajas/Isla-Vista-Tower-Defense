

#ifndef _LEVELGEN_H_
#define _LEVELGEN_H_

#include "cLevel.h"
#include "cGameStateBase.h"

class LevelGen : public GameStateBase {
public:
    virtual ~LevelGen() {}

    /**
    * Function: Init
    * Initiates the game state defaults.
    * Pre-conditions: None
    * Post-conditions: Depends on user.
    */
	virtual void Init();

    /**
    * Function: CleanUp
    * Deallocates any allocated memory.
    * Pre-conditions: None
    * Post-conditions: Depends on user.
    */
	virtual void Cleanup();

    /**
    * Function: DoState
    * Does the game base state.
    * Pre-conditions: None
    * Post-conditions: Depends on user.
    */
    virtual void DoState();

    /**
    * Function: GetEvents
    * Receives input events from the user.
    * Pre-conditions: None
    * Post-conditions: Depends on user.
    */
    virtual void GetEvents() {}

    /**
    * Function: Display
    * Displays the game base state.
    * Pre-conditions: None
    * Post-conditions: Depends on user.
    */
    virtual void Display() {}

    /**
    * Function: GetInstance
    * Is used to get the only instance of the MainMenu class.
    * Pre-conditions: None
    * Post-conditions: The only instance of MainMenu class is returned.
    */
	static LevelGen* GetInstance() {
	    static LevelGen m_levelgen;
        return &m_levelgen;
    }

protected:
    /**
    * The following constructors are used to help prevent additional creations of the
    * MainMenu class.
    */
    LevelGen() { }                       // Private constructor
    LevelGen(const LevelGen&);              // Prevent copy-construction
    LevelGen& operator= (const LevelGen&);  // Prevent assignment

private:
    Level *m_level;
};

#endif
