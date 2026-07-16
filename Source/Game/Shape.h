#pragma once

#include "raylib.h"
#include "Helpers/Vector.h"


class CShape
{
public:
    CShape();
    ~CShape();
    virtual void draw() = 0;
    void setPosition(float mouseX, float mouseY);
    void addScale();
    void resetScale();
    void breathingScale();
    

protected:
    vec2 Position;
    float Angles = 0.0f;
    vec2 Scale = 1;
    vec2 Breathing;
    double AddBreath = 0.0;

    Color ObjectColor;
};

