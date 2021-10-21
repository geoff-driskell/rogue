#include "components.hpp"

class StateComponent : public Component {
private:
    int xpos;
    int ypos;

public:
    StateComponent()
    {
        xpos = 0;
        ypos = 0;
    }
    
    StateComponent(int x, int y)
    {
        xpos = x;
        ypos = y;
    }

    int x() { return xpos; }
    int y() { return ypos; }

    void init() override {}

    void update() override {
        xpos++;
        ypos++;
    }

    void setPos(int x, int y) {
        xpos = x;
        ypos = y;
    }
};
