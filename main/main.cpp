#include <iostream>
#include "Game.h"

int main()
{
    // Initialize random seed
    srand(static_cast<unsigned>(time(0)));

    // Initialize Game object
    Game game;


    // Game loop
    while (game.isRunning())
    {
        // Update
        game.update();

        // Render
        game.render();
    }

    return 0;
}
