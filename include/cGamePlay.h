#ifndef _GAMEPLAY_H_
#define _GAMEPLAY_H_

#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>

#include "cApplication.h"

class GameStateBase;

using namespace std;

/**
* Class: GamePlay
* This class handles everything that has to do with logic regarding game states.
* Purpose: To control all the logic that has to do with taking in input and display images
* for the main menu screen.
*/
class GamePlay {
public:
    ~GamePlay() {}

    /**
    * Function: Init
    * Initiates the gameplay defaults and sets up the application window screen.
    * Pre-conditions: None
    * Post-conditions: The window is created to have dimensions of 640x480 and the frame limit
    * is set to 60.
    */
    void Init();

    /**
    * Function: Run
    * Initiates the first game state that is on the game play stack and pushes that state onto
    * the gameplay stack.
    * Pre-conditions: None
    * Post-conditions: Control of the screen is given to the game state base object on top of the stack.
    */
    void Run();

    /**
    * Function: Shutdown
    * Deletes all the objects that have been pushed onto the game play stack.
    * Pre-conditions: None
    * Post-conditions: Pops all game play states.  Application window is closed.
    */
	void Shutdown();

    /**
    * Function: DoState
    * Is called to do (run) the game state on top of the game play stack.
    * Pre-conditions: Must be a game state on top of the game play stack to 'do'.
    * Post-conditions: Control of the screen is given to the game state base object on top of the stack.
    */
	void DoState();

    /**
    * Function: ChangeState
    * Pops the current game base state off the top of the game play stack and pushes a state onto the stack.
    * Pre-conditions: Must have something on the stack to pop.
    * Post-conditions: A new state is pushed onto the stack.
    */
	void ChangeState(GameStateBase* state);

	/**
    * Function: PushState
    * A game base state is pushed onto the game play stack
    * Pre-conditions: None
    * Post-conditions: A new game base state is pushed on to the game play stack.
    */
	void PushState(GameStateBase* state);

	/**
    * Function: PopState
    * Pre-conditions: There must be a game base state on the game play stack.
    * Post-conditions: A game base state is pushed off the stack.
    */
	void PopState();

    /**
    * Function: Quit
    * Pre-conditions: None
    * Post-conditions: Closes Application window.
    */
	void Quit();

    /**
    * Function: GetInstance
    * Is used to get the only instance of the GamePlay class.
    * Pre-conditions: None
    * Post-conditions: The only instance of GamePlay class is returned.
    */
	static GamePlay &GetInstance() {
        static GamePlay instance;
        return instance;
    }

protected:
    /**
    * The following constructors are used to help prevent additional creations of the
    * GamePlay class.
    */
    GamePlay() {}                          // Private constructor
    GamePlay(const GamePlay&);              // Prevent copy-construction
    GamePlay& operator= (const GamePlay&);  // Prevent assignment

private:

    // Stack of states
	vector<GameStateBase*> m_states;
};

#endif /* _GAMEPLAY_H_ */
