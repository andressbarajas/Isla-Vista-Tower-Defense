
#include "../Drawables/cButton.h"
#include "../cGameStateBase.h"

#include <string>
#include <sstream>


class BasicButton : public Button {
public:

    BasicButton() { m_state = NULL; }

    virtual ~BasicButton() {}

    /**
    * Function: Draw
    * Takes the Application window (App) as a parameter to know which window to draw into.
    * Pre-conditions: None
    * Post-conditions: The button image is drawn on the screen
    */
    virtual void Draw(Application &App);

    //virtual void nextFrame() {}

    /**
    * Function: buttonEvent
    * Provides the user with the functionality to assign operations to the button when it is
    * highlighted, pressed, or disabled.
    * Pre-conditions: None
    * Post-conditions: Depends on user.
    */
    virtual void buttonEvent() {}

    /**
    * Function: setDescription
    * Gives a description to the tower button.
    * Pre-conditions: None
    * Post-conditions: The class member 'm_tower_desc' is given the value 'tower_description'.
    */
    inline void setDescription(string button_description) { m_button_desc = button_description; }

    /**
    * Function: getDescription
    * Returns the description of the tower button.
    * Pre-conditions: None
    * Post-conditions: Returns m_tower_desc.
    */
    void getDescription(string &desc) { }

    inline void setState(GameStateBase *state) { m_state = state; }

    inline GameStateBase* getState() { return m_state; }

private:
    string m_button_desc;
    GameStateBase *m_state;
};
