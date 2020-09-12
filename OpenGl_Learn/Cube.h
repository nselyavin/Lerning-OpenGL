#pragma once
#include "Geometry.h"

class Cube :
    public Geometry
{

public:
    Cube();
    Cube(float posx, float posy, float posz);

    void draw();
};

