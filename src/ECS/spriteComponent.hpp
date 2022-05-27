#pragma once

#include "components.hpp"
#include "Animation.hpp"
#include "../../include/SDL.h"
#include "../textureManager.hpp"
#include <map>
class SpriteComponent : public Component
{
private:
    StateComponent *state;
    SDL_Texture *texture;
    SDL_Rect srcRect, destRect;

    bool animated = false;
    int frames = 0;
    int speed = 100;

public:

    int animIndex = 0;

    std::map<const char*, Animation> animations;

    SpriteComponent() = default;
    SpriteComponent(const char* path)
    {
        setTexture(path);
    }

    SpriteComponent(const char* path, bool isAnimated)
    {
        animated = isAnimated;
        Animation charDown = Animation(0, 3, 100);
        Animation charLeft = Animation(1, 3, 100);
        Animation charRight = Animation(2, 3, 100);
        Animation charUp = Animation(3, 3, 100);

        animations.emplace("Down", charDown);
        animations.emplace("Left", charLeft);
        animations.emplace("Right", charRight);
        animations.emplace("Up", charUp);

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
        srcRect.y = 0;
        srcRect.w = state->width;
        srcRect.h = state->height;
        destRect.w = state->width * state->scale;
        destRect.h = state->height * state->scale;
    }

    void update() override
    {
        if (animated)
        {
            Uint32 tick = SDL_GetTicks();
            int frame = static_cast<int>(fmod((tick/speed), frames));
            
            srcRect.x = srcRect.w * frame;
        }

        srcRect.y = animIndex * state->height;
        
        destRect.x = static_cast<int>(state->position.x);
        destRect.y = static_cast<int>(state->position.y);
    }  

    void draw() override
    {
        TextureManager::Draw(texture, srcRect, destRect, SDL_FLIP_NONE);
    }

    void changeFrame(int frame, int direction)
    {
        srcRect.x = frame * srcRect.w;
        srcRect.y = direction * srcRect.h;
    }
};
