#pragma once
#include "Helpers/Vector.h"
#include "raylib.h"
#include "Helpers/Sprite2D.h"


class CGameObject // abstricte class 
{ 
public:
    CGameObject();
    ~CGameObject();

    virtual void update() = 0; // pure virtal function, must be override
    virtual void draw() = 0;

    vec2 getPosition();
    void setPosition(vec2 position);

protected:
    vec2 Position;
    float Angles = 0;
    vec2 Scale = 4;

    Color ObjectColor = RED;
};


class CPlayer : public CGameObject
{
public:
    CPlayer();
    ~CPlayer();
    void update() override;
    void draw() override;

    void setDirection(float dir) { Direction = dir; }

    int getSpriteSize();

private:

    Texture2D Texture;
    Sprite2D* Sprite;

    float MoveSpeed = 10.0f;
    float Direction = 0;
};

