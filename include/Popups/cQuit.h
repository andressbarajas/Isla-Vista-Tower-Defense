

#ifndef _QUIT_H_
#define _QUIT_H_

#include "cPopup.h"
#include "../Drawables/cBanner.h"
#include "../Panels/cMenuPanel.h"

class QuitGame : public Popup {
public:
    QuitGame();
    ~QuitGame() {}

    // Draw this drawable: Should be overwritten
	virtual void Draw(Application &App);

	// Handle the events
	virtual bool handleEvent(const sf::Input &Input);

	virtual void nextFrame() {}

	void setPauseMPosition(sf::Vector2f pos);

	//virtual void setPanel(MenuPanel *panel) { m_panel = panel; }

protected:

private:
    Banner m_banner;
    sf::Image m_image;
};

#endif

