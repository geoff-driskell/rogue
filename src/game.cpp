#include "game.hpp"
#include "textureManager.hpp"

SDL_Texture* playerTex;
SDL_Rect srcRect, destRect;

SDL_Renderer* Game::renderer = nullptr;

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

        Game::renderer = SDL_CreateRenderer(window, -1, 0);

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

    playerTex = TextureManager::LoadTexture("assets/knight_run.png");
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
    SDL_RenderCopy(Game::renderer, playerTex, &srcRect, &destRect);
    SDL_RenderPresent(Game::renderer);
}

void Game::clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(Game::renderer);
    SDL_Quit();
    std::cout << "Game cleaned." << std::endl;
}