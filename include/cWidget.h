
#ifndef _WIDGET_H_
#define _WIDGET_H_

#include <SFML/Window.hpp>

class Widget {
public:
	// Constructor / destructor
	Widget();
	virtual ~Widget();

	// Get/Set our focused state.
	virtual void setFocus(bool foc);
	bool getFocused() const { return m_focused; }

protected:
	bool	m_focused;	// Are we focused?
};

#endif	/* _WIDGET_H_ */


