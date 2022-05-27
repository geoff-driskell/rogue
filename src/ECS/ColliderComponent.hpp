#pragma once

#include <string>
#include "../../include/SDL.h"
#include "components.hpp"
#include "../textureManager.hpp"

class ColliderComponent : public Component
{
public:
    SDL_Rect collider;
    std::string tag;

    SDL_Texture* tex;
    SDL_Rect srcR, destR;

    StateComponent* state;

    ColliderComponent(std::string t)
    {
        tag = t;
    }

    ColliderComponent(std::string t, int xpos, int ypos, int size)
    {
        tag = t;
        collider.x = xpos;
        collider.y = ypos;
        collider.w = collider.h = size;
    }

    void init() override
    {
        if (!entity->hasComponent<StateComponent>())
        {
            entity->addComponent<StateComponent>();
        }
        state = &entity->getComponent<StateComponent>();

        tex = TextureManager::LoadTexture("assets/coltex.png");
        srcR = { 0, 0, 32, 32 };
        destR = { collider.x, collider.y, collider.w, collider.h};
        
        //Game::colliders.push_back(this);
    }

    void update() override
    {
        if (tag != "terrain")
        {
            collider.x = static_cast<int>(state->position.x);
            collider.y = static_cast<int>(state->position.y);
            collider.w = state->width * state->scale;
            collider.h = state->height * state->scale;
        }

        destR.x = collider.x - Game::camera.x;
        destR.y = collider.y - Game::camera.y;
    }

    void draw() override
    {
        TextureManager::Draw(tex, srcR, destR, SDL_FLIP_NONE);
    }
};
