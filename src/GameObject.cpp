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
    int sprite = (tick/100) % 3;
    srcRect.x = sprite * 32;
    srcRect.y = 2*32;
    srcRect.w = 32;
    srcRect.h = 32;
    destRect.x = xpos;
    destRect.y = ypos;
    destRect.w = 32;
    destRect.h = 32;
}

void GameObject::render()
{
    SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
}

