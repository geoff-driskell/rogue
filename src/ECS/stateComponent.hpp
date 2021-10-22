#pragma once
#include "components.hpp"
#include "../Vector2D.hpp"

class StateComponent : public Component 
{

public:
    Vector2D position;
    Vector2D velocity;

    int height = 32;
    int width = 32;
    int scale = 1;
    int speed = 3;



    StateComponent()
    {
        position.x = 0;
        position.y = 0;
    }
    
    StateComponent(double x, double y)
    {
        position.x = x;
        position.y = y;
    }

    StateComponent(double x, double y, int w, int h, int sc)
    {
        position.x = x;
        position.y = y;
        width = w;
        height = h;
        scale = sc;
    }

    void init() override
    {
        velocity.x = 0;
        velocity.y = 0;
    }

    void update() override
    {
        position.x += velocity.x * speed;
        position.y += velocity.y * speed;
    }
};
