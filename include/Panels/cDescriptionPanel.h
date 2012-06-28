
#ifndef _DESCRIPTIONPANEL_H_
#define _DESCRIPTIONPANEL_H_

#include <list>
#include <string>

#include "../cApplication.h"
#include "cPanelInterface.h"
#include "../Drawables/cButton.h"

/*
   Inherits PanelInterface class and holds the buttons that correspond to different towers that
   can be built. Also contains variables of class Money and class DescriptionalPanel so they can
   interact with the vector of buttons.
*/
class DescriptionPanel : public PanelInterface {
public:
    /**
    * Constructor
    * ***Currently Empty***
    * Pre-conditions: nothing.
    * Post-conditions: initializes DescriptionPanel members.
    */
    DescriptionPanel();
    virtual ~DescriptionPanel() {}
    /**
    * Function: Draw
    * Draws panel onto the Application Window
    * Pre-conditions: There is an existing application window
    * Post-conditions: This panel was drawn onto the application window.
    */
    virtual void Draw(Application &App);

    /**
    * Functin: moveObjects
    * moves child objects. see SpriteObj for more details.
    * ***CURRENTLY EMPTY***
    * Pre-conditions: nothing.
    * Post-conditions: Moves childeren with the panel.
    */
    virtual void moveObjects(const float x, const float y);

    virtual void nextFrame();

    void setDescPanelPosition(sf::Vector2f pos);

    void setHeader(char *header);
    void setDescription(string description);

private:
    sf::Image m_background;
    sf::String m_header;
    sf::String m_description;

    //copied_ptr<Button>
    //DescriptionPanel m_desc_panel;
//    Button m_buttons[4];
};

#endif /* _DESCRIPTIONPANEL_H_ */

