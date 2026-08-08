#pragma once

#include "raylib.h"
#include "GameState.h"
#include "Helpers/InputTypes.h"
#include "Helpers/Vector.h"

class CGame;
class Sprite2D;

class CBall
{
public:
    CBall(CGamePlay* gameplay);
    ~CBall();

    void reset();
    void update(float deltaTime);
    void draw();


    // Getters.
    vec2 getPosition() { return Position; }
    float getAngle()   { return Angle; }
    vec2 getScale()    { return Scale; }
    float getRadius()  { return Radius; }
    Color getColor()   { return ObjectColor; }
	vec2 getVelocity() { return Velocity; }

    // Setters.
    void setPosition(vec2 pos)   { Position = pos; }
    void setAngle(float angle)   { Angle = angle; }
    void setScale(vec2 scale)    { Scale = scale; }
    void setRadius(float radius) { Radius = radius; }
    void setColor(Color color)   { ObjectColor = color; }
    void setVelocity(vec2 vel)   { Velocity = vel; }

private:
    CGamePlay* GameState = nullptr;

    bool Active = false;

    vec2 Position = 0;
    float Angle = 0;
    vec2 Scale = 1;
    float Radius = 0;
    Color ObjectColor = WHITE;

    Sprite2D* Sprite;
    vec2 Controls = 0;
    vec2 Velocity = 0;
};
