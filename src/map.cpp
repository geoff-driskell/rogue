#include "map.hpp"
#include "game.hpp"
#include <fstream>

Map::Map()
{

}
Map::~Map()
{

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