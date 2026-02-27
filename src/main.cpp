import Game;

#include "constants.hpp"

int main()
{
    Game game(CONSTANTS::WINDOW_WIDTH, CONSTANTS::WINDOW_HEIGHT);
    game.run();
    return 0;
}