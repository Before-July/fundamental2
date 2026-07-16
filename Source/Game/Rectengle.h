#pragma once
//#include "raylib.h"
//#include "Helpers/Vector.h"
#include "Shape.h"

class CRectengle : public CShape
{
public:
    CRectengle();
    //CRectengle(float x, float y, float scale);
    ~CRectengle();
    void draw() override;

private:
    float Height;
    float Width;
};

