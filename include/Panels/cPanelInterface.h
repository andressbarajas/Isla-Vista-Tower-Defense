
#ifndef _PANELINTERFACE_H_
#define _PANELINTERFACE_H_

#include "../cSpriteObj.h"
#include "../cApplication.h"
#include <SFML/System/Vector2.hpp>

/*
   Acts as a seperate window(inside the window frame of the application) to draw into.
   Multiple panels can be displayed in the window frame of the application.  This allows
   for better organization of a GUI.
*/
class PanelInterface : public SpriteObj {
public:
    PanelInterface() { }
    virtual ~PanelInterface() { }
    //Draws PanelInterface onto Application window
    virtual void Draw(Application &App)=0;
    //Handless events that occur on panel interface
    //virtual bool handleEvent(const sf::Input& Input);
    //moves children objects see SpriteObj class
    virtual void moveObjects(const float x, const float y)=0;
private:
};

#endif
