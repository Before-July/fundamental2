#pragma once
#include "Helpers/Vector.h"
#include "raylib.h"
#include "Helpers/Sprite2D.h"
#include "Helpers/InputTypes.h"
#include "Collision.h"
#include <string>
#include <vector>

class CCollision;

class CGameObject // abstricte class 
{ 
public:
    CGameObject();
    ~CGameObject();

    virtual void onKey(int keyCode, KeyState keyState);
    virtual void update(float deltaTime) = 0; // pure virtal function, must be override
    virtual void draw() = 0;

    vec2 getPosition();
    void setPosition(vec2 position);

protected:
    vec2 Position;
    float Angles = 0;
    vec2 Scale = 4;
    float Direction = 0;
    bool flip = false;
    Color ObjectColor = RED;
};


class CPlayer : public CGameObject
{
public:
    CPlayer();
    ~CPlayer();
    void update(float deltaTime) override;
    void draw() override;

    //void setDirection(float dir) { Direction = dir; }
    int getSpriteSize();
    void loadAnimation(std::string ani_name, int num_frame, float fps);

private:

    Texture2D Texture;
    Sprite2D* Sprite;
    std::vector<Sprite2D*> Animation;
    
    float AnimationFPS = 0.0f;
    float AnimationTimer = 0.0f;
    int FrameCount = 0;
    float MoveSpeed = 300.0f;

};

class CFloor
{
public:
    CFloor();
    ~CFloor();
    vec2 getPoint(int whichPoint);
    void draw();

private:
    vec2 Position;
    vec2 TopLeft;
    vec2 TopRight;
    vec2 BottomLeft;
    vec2 BottomRight;
    CCollision* Collision;

};

