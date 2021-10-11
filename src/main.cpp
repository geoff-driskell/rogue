#include "game.hpp"

Game *game = nullptr;
bool firstFrame = true;

int main(int argc, const char * argv[])
{
    const int fps = 60;
    const int framePlanned = 1000 / fps;
    int frameDifference;

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

        if (firstFrame)
        {
            SDL_Delay(17);
            firstFrame = false;
        }

        frameActual = SDL_GetTicks() - frameStart;

        frameDifference = framePlanned - frameActual;

        if (frameDifference > 0)
        {
            SDL_Delay(frameDifference);
            std::cout << "Game is ahead, delaying by " << frameDifference << " milliseconds." << std::endl;
        }
        else if (frameDifference == 0)
        {
            std::cout << "Game is on time, continuing..." << std::endl;
        }
        else
        {
            std::cout << "Game is behind by " << abs(frameDifference) << " milliseconds. Hopefully we catch up." << std::endl;
        }
    }

    game->clean();
}