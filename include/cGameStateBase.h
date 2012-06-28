
#ifndef _GAMESTATE_H_
#define _GAMESTATE_H_

class GamePlay;

/**
* Class: GameStateBase
* This class handles everything that has to do with logic regarding game states.
* Purpose: To control all the logic that has to do with taking in input and display images
* for the main menu screen.
*/
class GameStateBase {
public:

    /**
    * Constructor
    * Pre-conditions: None
    * Post-conditions: A GameStateObject is created.
    */
    GameStateBase() {}
    virtual ~GameStateBase() {}

    /**
    * Function: Init
    * Initiates the game state defaults.
    * Pre-conditions: None
    * Post-conditions: Depends on user.
    */
	virtual void Init()=0;

    /**
    * Function: CleanUp
    * Deallocates any allocated memory.
    * Pre-conditions: None
    * Post-conditions: Depends on user.
    */
	virtual void Cleanup()=0;

    /**
    * Function: DoState
    * Does the game base state.
    * Pre-conditions: None
    * Post-conditions: Depends on user.
    */
    virtual void DoState()=0;

    /**
    * Function: GetEvents
    * Receives input events from the user.
    * Pre-conditions: None
    * Post-conditions: Depends on user.
    */
    virtual void GetEvents()=0;

    /**
    * Function: Display
    * Displays the game base state.
    * Pre-conditions: None
    * Post-conditions: Depends on user.
    */
    virtual void Display()=0;

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

protected:
    /*
	GameStateBase() { }                               // Private constructor
	GameStateBase(const GameStateBase&);              // Prevent copy-construction
    GameStateBase& operator= (const GameStateBase&);  // Prevent assignment
    */
private:
};

#endif /* _GAMESTATE_H_ */
