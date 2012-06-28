#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#include <SFML/Graphics.hpp>

/**
* Class: Application
* Purpose: Acts as a wrapper around the sf::RenderWindow class to create
* a singleton class. Handles the window frame of the application
* and the events(user input) associated with it.
*/
class Application : public sf::RenderWindow {
public:
    ~Application() {}

    /**
    * Function: GetInstance
    * Is used to get the only instance of the Application class.
    * Pre-conditions: None
    * Post-conditions: The only instance of Application class is returned.
    */
	static Application& GetInstance() {
        static Application instance;
        return instance;
    }

protected:
    /**
    * The following constructors are used to help prevent additional creations of the
    * Application class.
    */
    Application() {}                             // Private constructor
    Application(const Application&);              // Prevent copy-construction
    Application& operator= (const Application&);  // Prevent assignment

private:

};

#endif /* _APPLICATION_H_ */
