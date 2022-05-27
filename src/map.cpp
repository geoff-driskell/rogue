#include "map.hpp"
#include "game.hpp"
#include <fstream>
#include "ECS/ECS.hpp"
#include "ECS/TileComponent.hpp"

extern Manager manager;

Map::Map(const char* p_mapFilePath, int p_mapScale, int p_tileSize)
{
    m_scaledSize = p_mapScale * p_tileSize;
}

Map::~Map()
{

}

void Map::loadMap(std::string path, int sizeX, int sizeY)
{
    char c;
    std::fstream mapFile;
    mapFile.open(path);

    int srcX, srcY;
    
    for (int y = 0; y < sizeY; y++)
    {
        for (int x = 0; x < sizeX; x++)
        {
            mapFile.get(c);
            srcY = atoi(&c) * m_tileSize;
            mapFile.get(c);
            srcX = atoi(&c) * m_tileSize;
            AddTile(srcX, srcY, x * m_scaledSize, y * m_scaledSize);
            mapFile.ignore();
        }
        mapFile.ignore();
    }
    
    for (int y = 0; y < sizeY; y++)
    {
        for (int x = 0; x < sizeX; x++)
        {
            mapFile.get(c);
            if (c == '1')
            {
                auto& tcol(manager.addEntity());
                tcol.addComponent<ColliderComponent>(("terrain"), x * m_scaledSize, y * m_scaledSize, m_scaledSize);
                mapFile.ignore();
            }
            mapFile.ignore();
        }
    }

    mapFile.close();
}
void Map::AddTile(int srcX, int srcY, int xpos, int ypos) 
{
    auto& tile(manager.addEntity());
    tile.addComponent<TileComponent>(srcX, srcY, xpos, ypos, m_tileSize, m_mapScale, m_mapFilePath);
    tile.addGroup(Game::groupMap);
}
