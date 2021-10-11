#ifndef Game_hpp
#define Game_hpp
#include "../include/SDL2/SDL.h"
#include "../include/SDL2_image/SDL_image.h"
#include <stdio.h>
#include <iostream>

class Game {

public:
    Game();
    ~Game();

    void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
    
    void handleEvents();
    void update();
    void render();
    void clean();

    bool running() { return isRunning; }

private:
    bool isRunning;
    SDL_Window* window;
    SDL_Renderer* renderer;
    int count = 0;
};


#endif /* Game_hpp */