#include "game.hpp"

SDL_Texture* playerTex;
SDL_Rect srcRect, destRect;

Game::Game()
{}
Game::~Game()
{}

void Game::init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen)
{
    int flags = 0;
    if (fullscreen)
    {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        std::cout << "Subsystems initialized!..." << std::endl;

        window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        if (window)
        {
            std::cout << "Window has been created." << std::endl;
        }

        renderer = SDL_CreateRenderer(window, -1, 0);

        if (renderer)
        {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            std::cout << "Renderer has been created!" << std::endl;
        }

        isRunning = true;
    }
    else
    {
        isRunning = false;
    }

    SDL_Surface* tmpSurface = IMG_Load("assets/knight_run.png");
    playerTex = SDL_CreateTextureFromSurface(renderer, tmpSurface);
    SDL_FreeSurface(tmpSurface);
}

void Game::handleEvents()
{
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type)
    {
    case SDL_QUIT:
        isRunning = false;
        break;
    
    default:
        break;
    }
}

void Game::update()
{
    count++;
    Uint32 tick = SDL_GetTicks();
    int sprite = (tick/100) % 10;
    srcRect.x = sprite * 120;
    srcRect.y = 0;
    srcRect.w = 120;
    srcRect.h = 80;
    destRect.x = count;
    destRect.y = 0;
    destRect.w = 120;
    destRect.h = 80;
    
    std::cout << count << std::endl;
}

void Game::render()
{
    SDL_RenderClear(renderer);
    // add stuff to render
    SDL_RenderCopy(renderer, playerTex, &srcRect, &destRect);
    SDL_RenderPresent(renderer);
}

void Game::clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "Game cleaned." << std::endl;
}