#pragma once
#include <vector>

#include "raylib.h"
#include "Helpers/InputTypes.h"
#include "Helpers/Vector.h"
#include "Shape.h"

class CStampsGame 
{
public:
    CStampsGame();
    ~CStampsGame();

    void update(float deltaTime);
    void draw();

    // Input event methods.
    void onKey(int keyCode, KeyState keyState);
    void onMouseButton(int button, KeyState keyState);
    void onMouseMove(float x, float y);

private:

    std::vector<CShape*> AddShapes;
    CShape* NewShape[4];
    CShape* ShowShape[4];
    int WhichShape = 0;

};

