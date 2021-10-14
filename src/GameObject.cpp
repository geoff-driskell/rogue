#include "GameObject.hpp"
#include "textureManager.hpp"

GameObject::GameObject(const char* texturesheet, int x, int y)
{
    objTexture = TextureManager::LoadTexture(texturesheet);
    xpos = x;
    ypos = y;
}

void GameObject::update()
{
    xpos++;
    
    Uint32 tick = SDL_GetTicks();
    int sprite = (tick/100) % 10;
    srcRect.x = sprite * 120;
    srcRect.y = 0;
    srcRect.w = 120;
    srcRect.h = 80;
    destRect.x = xpos;
    destRect.y = ypos;
    destRect.w = 120;
    destRect.h = 80;
}

void GameObject::render()
{
    SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
}

