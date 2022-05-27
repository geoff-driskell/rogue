#include "map.hpp"
#include "game.hpp"
#include <fstream>

Map::Map()
{
    dirt = TextureManager::LoadTexture("assets/maps/Dirt1.png");
    grass = TextureManager::LoadTexture("assets/maps/Grass1.png");
    water = TextureManager::LoadTexture("assets/maps/Water1.png");
    wall = TextureManager::LoadTexture("assets/maps/Wall-Up1.png");

    loadMap(level1);

    src.x = 0;
    src.y = 4*32;
    src.w = dest.w = 32;
    src.h = dest.h = 32;

    dest.x = dest.y = 0;
    
}
Map::~Map()
{
    SDL_DestroyTexture(grass);
    SDL_DestroyTexture(water);
    SDL_DestroyTexture(dirt);
    SDL_DestroyTexture(wall);
}

void Map::loadMap(int arr[20][25])
{
    for (int row = 0; row < 20; row++){
        for (int column = 0; column < 25; column++)
        {
            map[row][column] = arr[row][column];
        }
    }
}

void Map::drawMap()
{
    int type = 0;
    for (int row = 0; row < 20; row++){
        for (int column = 0; column < 25; column++)
        {
            type = map[row][column];
            dest.x = column * 32;
            dest.y = row * 32;

            switch (type)
            {
            case 0:
                TextureManager::Draw(water, src, dest);
                break;
            case 1:
                TextureManager::Draw(grass, src, dest);
                break;
            case 2:
                TextureManager::Draw(dirt, src, dest);
            
            default:
                break;
            }
        }
    }
}