#pragma once

#include <assert.h>
#include <string>
#include <unordered_map>
#include <vector>

#include "raylib.h"
#include "Helpers/InputTypes.h"
#include "Helpers/Vector.h"
#include "Ball.h"
#include "Player.h"
#include "Shape.h"

class CBall;
class CPlayer;

class CGame
{
public:
    CGame();
    virtual ~CGame();

    void reset();
    void update(float deltaTime);
    void draw();

    // Input event methods.
    void onKey(int keyCode, KeyState keyState);
    void onMouseButton(int button, KeyState keyState);
    void onMouseMove(float x, float y);

    // Getters.
    CBall* getBall() { return Ball; }

    Texture2D getTexture(const char* textureName) const;

private:
    std::unordered_map<std::string, Texture2D> Textures;

    CBall* Ball = nullptr;
    CPlayer* Player = nullptr;

    std::vector<CShape*> AddShapes;
    CShape* NewShape[4];
    CShape* ShowShape[4];
    int WhichShape = 0;
};
