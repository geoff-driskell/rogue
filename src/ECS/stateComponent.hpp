#pragma once
#include "components.hpp"
#include "../Vector2D.hpp"

class StateComponent : public Component 
{

public:
    Vector2D position;

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

    void update() override
    {
        
    }
};
