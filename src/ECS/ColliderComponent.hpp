#pragma once

#include <string>
#include "../../include/SDL.h"
#include "components.hpp"

class ColliderComponent : public Component
{
public:
    SDL_Rect collider;
    std::string tag;

    StateComponent* state;

    ColliderComponent(std::string t)
    {
        tag = t;
    }

    void init() override
    {
        if (!entity->hasComponent<StateComponent>())
        {
            entity->addComponent<StateComponent>();
        }
        state = &entity->getComponent<StateComponent>();

        Game::colliders.push_back(this);
    }

    void update() override
    {
        collider.x = static_cast<int>(state->position.x);
        collider.y = static_cast<int>(state->position.y);
        collider.w = state->width * state->scale;
        collider.h = state->height * state->scale;
    }
};
