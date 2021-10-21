#pragma once

#include "components.hpp"
#include "../../include/SDL.h"
#include "../textureManager.hpp"

class SpriteComponent : public Component
{
private:
    StateComponent *state;
    SDL_Texture *texture;
    SDL_Rect srcRect, destRect;

public:
    SpriteComponent() = default;
    SpriteComponent(const char* path)
    {
        setTexture(path);
    }
    
    void setTexture(const char* path)
    {
        texture = TextureManager::LoadTexture(path);
    }

    void init() override
    {
        state = &entity->getComponent<StateComponent>();
        
        srcRect.x = 0;
        srcRect.y = 64;
        srcRect.w = srcRect.h = 32;
        destRect.w = destRect.h = 32;
    }

    void update() override
    {
        destRect.x = (int)state->position.x;
        destRect.y = (int)state->position.y;
    }  

    void draw() override
    {
        TextureManager::Draw(texture, srcRect, destRect);
    }

    void changeFrame(int frame)
    {
        srcRect.x = frame * srcRect.w;
    }
};
