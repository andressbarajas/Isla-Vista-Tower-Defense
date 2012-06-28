

#ifndef _POPUP_H_
#define _POPUP_H_

#include "../cSpriteObj.h"

class MenuPanel;

class Popup : public SpriteObj {
public:

    Popup() { m_panel = NULL; }
    ~Popup() {}

    virtual void setPanel(MenuPanel *panel) { m_panel = panel; }
protected:
    MenuPanel *m_panel;
};

#endif /* _POPUP_H_ */
