#include "game.hpp"

Game *game = nullptr;

int main(int argc, const char * argv[])
{
    const int fps = 60;
    const int framePlanned = 1000 / fps;

    uint32_t frameStart;
    int frameActual;

    
    game = new Game();
    game->init("GeoffGame", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);

    while (game->running()) 
    {
        frameStart = SDL_GetTicks();


        game->handleEvents();
        game->update();
        game->render();

        frameActual = SDL_GetTicks() - frameStart;

        if (frameActual < framePlanned)
        {
            SDL_Delay(framePlanned - frameActual);
        }
    }

    game->clean();
}