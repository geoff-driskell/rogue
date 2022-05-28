#include "game.hpp"
#include "textureManager.hpp"
#include "map.hpp"
#include "ECS/components.hpp"
#include "Vector2D.hpp"
#include "Collision.hpp"

Map* map;
Manager manager;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

SDL_Rect Game::camera = {0,0,800,640};

bool Game::isRunning = false;

auto& player(manager.addEntity());

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

        Game::isRunning = true;
    }
    else
    {
        Game::isRunning = false;
    }

    map = new Map("assets/terrain_ss.png", 3, 32);

    map->loadMap("assets/maps/map.map", 25, 20);

    player.addComponent<StateComponent>(2);
    player.addComponent<SpriteComponent>("assets/Male/Male 01-1.png", true);
    player.addComponent<KeyboardController>();
    player.addComponent<ColliderComponent>("player");
    player.addGroup(groupPlayers);
}

auto& tiles(manager.getGroup(Game::groupMap));
auto& players(manager.getGroup(Game::groupPlayers));
auto& colliders(manager.getGroup(Game::groupColliders));

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

    SDL_Rect playerCollider = player.getComponent<ColliderComponent>().collider;
    Vector2D playerPosition = player.getComponent<StateComponent>().position;

    manager.refresh();
    manager.update();

    for (auto& collider : colliders)
    {
        SDL_Rect mapCollider = collider->getComponent<ColliderComponent>().collider;
        if (Collision::AABB(mapCollider, playerCollider))
        {
            player.getComponent<StateComponent>().position = playerPosition;
        }
    }

    camera.x = player.getComponent<StateComponent>().position.x - 384;
    camera.y = player.getComponent<StateComponent>().position.y - 304;

    if (camera.x < 0)
    {
        camera.x = 0;
    }
    if (camera.y < 0)
    {
        camera.y = 0;
    }
    if (camera.x > camera.w)
    {
        camera.x = camera.w;
    }
    if (camera.y > camera.h)
    {
        camera.y = camera.h;
    }
}


void Game::render()
{
    SDL_RenderClear(renderer);
    for (auto& t : tiles)
    {
        t->draw();
    }
    for (auto& c : colliders)
    {
        c->draw();
    }
    for (auto& p : players)
    {
        p->draw();
    }
    SDL_RenderPresent(Game::renderer);
}

void Game::clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(Game::renderer);
    SDL_Quit();
    std::cout << "Game cleaned." << std::endl;
}

