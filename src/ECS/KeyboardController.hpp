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
            switch (Game::event.key.keysym.sym)
            {
            case SDLK_w:
                state->velocity.y = -1;
                sprite->Play("Up");
                break;
            case SDLK_a:
                state->velocity.x = -1;
                sprite->Play("Left");
                break;
            case SDLK_d:
                state->velocity.x = 1;
                sprite->Play("Right");
                break;
            case SDLK_s:
                state->velocity.y = 1;
                sprite->Play("Down");
                break;
            case SDLK_UP:
                state->velocity.y = -1;
                sprite->Play("Up");
                break;
            case SDLK_LEFT:
                state->velocity.x = -1;
                sprite->Play("Left");
                break;
            case SDLK_RIGHT:
                state->velocity.x = 1;
                sprite->Play("Right");
                break;
            case SDLK_DOWN:
                state->velocity.y = 1;
                sprite->Play("Down");
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
                sprite->Pause("Up");
                break;
            case SDLK_a:
                state->velocity.x = 0;
                sprite->Pause("Left");
                break;
            case SDLK_d:
                state->velocity.x = 0;
                sprite->Pause("Right");
                break;
            case SDLK_s:
                state->velocity.y = 0;
                sprite->Pause("Down");
            case SDLK_UP:
                state->velocity.y = 0;
                sprite->Pause("Up");
                break;
            case SDLK_LEFT:
                state->velocity.x = 0;
                sprite->Pause("Left");
                break;
            case SDLK_RIGHT:
                state->velocity.x = 0;
                sprite->Pause("Right");
                break;
            case SDLK_DOWN:
                state->velocity.y = 0;
                sprite->Pause("Down");
                break;
            case SDLK_ESCAPE:
                Game::isRunning = false;
            default:
                break;
            }
        }
    }

};