#include "../include/SDL2/SDL.h"
#include <iostream>

using namespace std;

int main(){
    int width=800, height=600;
    SDL_Window *window=SDL_CreateWindow("Window", SDL_WINDOWPOS_CENTERED, 
    SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_RESIZABLE);

    if(window==NULL)
        cout << "There was an error while initializing the window" << endl << SDL_GetError() << endl;

    SDL_Event event;
    bool running=true;

    while(running){
        while(SDL_PollEvent(&event)){
            if(event.type==SDL_QUIT){
                running=false;
                break;
            }
        }
        SDL_GetWindowSize(window, &width, &height);

        SDL_Surface *surface=SDL_GetWindowSurface(window);
        Uint32 green=SDL_MapRGB(surface->format, 0,255,0);
        SDL_FillRect(surface, NULL, green);
        SDL_UpdateWindowSurface(window);
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
}