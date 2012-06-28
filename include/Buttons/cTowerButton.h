
#include "../Drawables/cButton.h"

#include <string>
#include <sstream>
#include <SFML/Graphics/String.hpp>

/**
* Class: TowerButton
* TowerButton inherits Button class so that polymorphism may be used.
* Purpose: To hold the properties(descriptions) of the tower buttons.
*/
class TowerButton : public Button {
public:

    /**
    * Constructor
    * Calls the default Button constructor.
    * Pre-conditions: None
    * Post-conditions: Superclass(Button) protected variables are assigned default values.
    */
    TowerButton() {}

    virtual ~TowerButton() {}

    /**
    * Function: Draw
    * Takes the Application window (App) as a parameter to know which window to draw into.
    * Pre-conditions: None
    * Post-conditions: The button image is drawn on the screen
    */
    virtual void Draw(Application &App);

    virtual void nextFrame();

    /**
    * Function: buttonEvent
    * Provides the user with the functionality to assign operations to the button when it is
    * highlighted, pressed, or disabled.
    * Pre-conditions: None
    * Post-conditions: Depends on user.
    */
    virtual void buttonEvent();

    /**
    * Function: setDescription
    * Gives a description to the tower button.
    * Pre-conditions: None
    * Post-conditions: The class member 'm_tower_desc' is given the value 'tower_description'.
    */
    void setDescription(string tower_description) { m_tower_desc = tower_description; }

    /**
    * Function: getDescription
    * Returns the description of the tower button.
    * Pre-conditions: None
    * Post-conditions: Returns m_tower_desc.
    */
    void getDescription(string &desc); //{ return m_tower_desc; }

    void disable(unsigned int money);

    void setCost(unsigned int cost) { m_cost = cost; }

private:
    string m_tower_desc;
    unsigned int m_cost;
};

