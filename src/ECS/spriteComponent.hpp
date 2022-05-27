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
    ~SpriteComponent()
    {
        SDL_DestroyTexture(texture);
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
        srcRect.w = state->width;
        srcRect.h = state->height;
        destRect.w = state->width * state->scale;
        destRect.h = state->height * state->scale;
    }

    void update() override
    {
        destRect.x = static_cast<int>(state->position.x);
        destRect.y = static_cast<int>(state->position.y);
    }  

    void draw() override
    {
        TextureManager::Draw(texture, srcRect, destRect);
    }

    void Play(const char* animName)
    {
        frames = animations[animName].frames;
        animIndex = animations[animName].index;
        speed = animations[animName].speed;
    }

    void Pause(const char* animName)
    {
        frames = 0;
        animIndex = animations[animName].index;
        speed = animations[animName].speed;
    }
};
