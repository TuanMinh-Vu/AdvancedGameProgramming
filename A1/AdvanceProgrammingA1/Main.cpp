#include "Game.h"

int main()
{
    Game* myGame = new Game(1400, 1000, "Advanced Game Programming - Assginemnet 1");
    myGame->Run();
    delete myGame;
    return 0;
}