#include "game.hpp"
#include "textureManager.hpp"
#include "map.hpp"
#include "ECS/components.hpp"
#include "Vector2D.hpp"
#include "Collision.hpp"

Map* map;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

std::vector<ColliderComponent*> Game::colliders;

Manager manager;
auto& player(manager.addEntity());
auto& wall(manager.addEntity());

auto& tile0(manager.addEntity());
auto& tile1(manager.addEntity());
auto& tile2(manager.addEntity());

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

    map = new Map();

    tile0.addComponent<TileComponent>(200,200,32,32,0);
    tile1.addComponent<TileComponent>(250,250,32,32,1);
    tile1.addComponent<ColliderComponent>("dirt");
    tile2.addComponent<TileComponent>(150,150,32,32,2);
    tile2.addComponent<ColliderComponent>("grass");


    player.addComponent<StateComponent>(100, 100);
    player.addComponent<SpriteComponent>("assets/Male/Male 01-1.png");
    player.addComponent<KeyboardController>();
    player.addComponent<ColliderComponent>("player");

    wall.addComponent<StateComponent>(300.0, 300.0, 20, 300, 1);
    wall.addComponent<SpriteComponent>("assets/maps/Wall-Up1.png");
    wall.addComponent<ColliderComponent>("wall");
}

void Game::handleEvents()
{
    

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
    manager.refresh();
    manager.update();

    for (auto cc : colliders)
    {
        Collision::AABB(player.getComponent<ColliderComponent>(), *cc);
    }
    
}

void Game::render()
{
    SDL_RenderClear(renderer);
    // add stuff to render
    //map->drawMap();
    manager.draw();
    SDL_RenderPresent(Game::renderer);
}

void Game::clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(Game::renderer);
    SDL_Quit();
    std::cout << "Game cleaned." << std::endl;
}

void Game::AddTile(int srcX, int srcY, int xpos, int ypos)
{
    auto& tile(manager.addEntity());
    tile.addComponent<TileComponent>(srcX, srcY, xpos, ypos, mapfile);
    tile.addGroup(groupMap);
}

