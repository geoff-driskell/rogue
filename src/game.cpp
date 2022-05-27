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

const char* mapfile = "assets/maps/terrain_ss.png";

enum groupLabels : std::size_t
{
    groupMap,
    groupPlayers,
    groupEnemies,
    groupColliders
};

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
        window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        Game::renderer = SDL_CreateRenderer(window, -1, 0);

        if (renderer)
        {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        }

        isRunning = true;
    }
    else
    {
        isRunning = false;
    }

    map = new Map();

    Map::loadMap("assets/maps/map.map", 25, 20);

    player.addComponent<StateComponent>(100, 100, 2);
    player.addComponent<SpriteComponent>("assets/Male/Male 01-1.png", true);
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

