#pragma once
#include <string>

class Map
{

public:
    Map(const char* p_mapFilePath, int p_mapScale, int p_tileSize);
    ~Map();

    void loadMap(std::string path, int sizeX, int sizeY);
    void AddTile(int srcX, int srcY, int xpos, int ypos);


private:
    const char* m_mapFilePath;
    int m_mapScale;
    int m_tileSize;
    int m_scaledSize;

};