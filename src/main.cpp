
#include <ctime>
#include <cmath>
#include "../include/cGamePlay.h"

int main() {

    /* Get an instance of the GamePlay Class */
    GamePlay &Game = GamePlay::GetInstance();

    /* Called so the random number can be used */
    srand((long)time(0));

    /* Setup the Window */
    Game.Init();

    /* Run the program */
    Game.Run();

    /* Clean up any allocated Memory before closing */
    Game.Shutdown();

	return EXIT_SUCCESS;
}
