#pragma once

#include <string>
#include "../../include/SDL.h"
#include "components.hpp"

class ColliderComponent : public Component
{
    SDL_Rect collider;
    std::string tag;

    StateComponent* state;

    void init() override
    {
        if (!entity->hasComponent<StateComponent>())
        {
            entity->addComponent<StateComponent>();
        }
        state = &entity->getComponent<StateComponent>();
    }
};
