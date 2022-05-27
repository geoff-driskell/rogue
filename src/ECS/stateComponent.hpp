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
        position.Zero();
    }
    
    StateComponent(int sc)
    {
        position.x = 384;
        position.y = 304;
        scale = sc;
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
        velocity.Zero();
    }

    void update() override
    {
        position.x += velocity.x * speed;
        position.y += velocity.y * speed;
    }
};
