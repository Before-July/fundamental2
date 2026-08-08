#pragma once

#include <assert.h>
#include <string>
#include <unordered_map>
#include <vector>

#include "raylib.h"
#include "Helpers/InputTypes.h"
#include "Helpers/Vector.h"
#include "Ball.h"
#include "GameObject.h"
#include "Bullet.h"

enum class GameState
{
    Title,
    GamePlay,
    Result
};

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

private:

};
