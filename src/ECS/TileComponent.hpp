#pragma once

#include "../../include/SDL.h"
#include "ECS.hpp"
#include "stateComponent.hpp"
#include "spriteComponent.hpp"

class TileComponent : public Component
{
public:
    StateComponent* state;
    SpriteComponent* sprite;

    SDL_Rect tileRect;
    int tileID;
    const char* path;

    TileComponent() = default;

    TileComponent(int x, int y, int w, int h, int id)
    {
        tileRect.x = x;
        tileRect.y = y;
        tileRect.w = w;
        tileRect.h = h;
        tileID = id;

        switch (tileID)
        {
        case 0:
            path = "assets/maps/Water1.png"
            break;
        case 1:
            path = "assets/maps/Dirt1.png"
            break;
        case 2:
            path = "assets/maps/Grass1.png"
            break;
        default:
            break;
        }
    }

    void init() override
    {
        entity->addComponent<StateComponent>(tileRect.x, tileRect.y, tileRect.w, tileRect.h, 1);
        state = &entity->getComponent<StateComponent>();

        entity->addComponent<SpriteComponent>(path);
        sprite = &entity->getComponent<SpriteComponent>();
    }
}