#include "game.hpp"
#include "textureManager.hpp"
#include "GameObject.hpp"
#include "map.hpp"

GameObject* player;
Map* map;

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

    player = new GameObject("assets/Male/Male 01-1.png", 0, 0);
    map = new Map();
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
    player->update();
}

void Game::render()
{
    SDL_RenderClear(renderer);
    // add stuff to render
    map->drawMap();
    player->render();
    SDL_RenderPresent(Game::renderer);
}

void Game::clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(Game::renderer);
    SDL_Quit();
    std::cout << "Game cleaned." << std::endl;
}