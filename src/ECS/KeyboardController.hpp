#pragma once

#include "../game.hpp"
#include "ECS.hpp"
#include "components.hpp"

class KeyboardController : public Component
{
public:
    StateComponent* state;
    SpriteComponent* sprite;

    void init() override
    {
        state = &entity->getComponent<StateComponent>();
        sprite = &entity->getComponent<SpriteComponent>();
    }

    void update() override
    {
        if (Game::event.type == SDL_KEYDOWN)
        {
            Uint32 tick = SDL_GetTicks();
            int frame = (tick/100) % 3;
            switch (Game::event.key.keysym.sym)
            {
            case SDLK_w:
                state->velocity.y = -1;
                sprite->changeFrame(frame, 3);
                break;
            case SDLK_a:
                state->velocity.x = -1;
                sprite->changeFrame(frame, 1);
                break;
            case SDLK_d:
                state->velocity.x = 1;
                sprite->changeFrame(frame, 2);
                break;
            case SDLK_s:
                state->velocity.y = 1;
                sprite->changeFrame(frame, 0);
                break;
            default:
                break;
            }
        }

        if (Game::event.type == SDL_KEYUP)
        {
            switch (Game::event.key.keysym.sym)
            {
            case SDLK_w:
                state->velocity.y = 0;
                break;
            case SDLK_a:
                state->velocity.x = 0;
                break;
            case SDLK_d:
                state->velocity.x = 0;
                break;
            case SDLK_s:
                state->velocity.y = 0;
            
            default:
                break;
            }
        }
    }

};