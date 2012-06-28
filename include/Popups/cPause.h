
#ifndef _PAUSE_H_
#define _PAUSE_H_

#include "cPopup.h"
#include "../Drawables/cBanner.h"

class Pause : public Popup {
public:
    Pause();
    ~Pause() {}

    // Draw this drawable: Should be overwritten
	virtual void Draw(Application &App);

	// Handle the events
	virtual bool handleEvent(const sf::Input &Input);

	virtual void nextFrame() {}

	void setPauseMPosition(sf::Vector2f pos);

protected:

private:
    Banner m_banner;
    sf::Image m_image;
};

#endif
