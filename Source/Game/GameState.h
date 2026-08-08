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


class CGameState
{
public:
    CGameState();
    ~CGameState();

    virtual void update(float deltaTime) = 0;
    virtual void draw() = 0;

    virtual void onKey(int keyCode, KeyState keyState) = 0;
    virtual void onMouseButton(int button, KeyState keyState) = 0;
    virtual void onMouseMove(float x, float y) = 0;


};

class CTitle : public CGameState
{

};

class CGamePlay : public CGameState
{
public:
    CGamePlay();
    ~CGamePlay();

    void reset();
    void update(float deltaTime) override;
    void draw() override;

    // Input event methods.
    void onKey(int keyCode, KeyState keyState) override;
    void onMouseButton(int button, KeyState keyState) override;
    void onMouseMove(float x, float y) override;

    // Getters.
    CBall* spawnBall(vec2 position, vec2 velocity);

    Texture2D getTexture(const char* textureName) const;

private:

    const int num_bullet = 3;

    std::unordered_map<std::string, Texture2D> Textures;

    CPlayer* Player = nullptr;

    std::vector<CBall*> BallPool;
    std::vector<CBall*> ActiveBall;

    //CBullet* bullet = nullptr;
    std::vector<CBullet*> Bullet;

    static const int num_MaxBalls = 20;
};

class CResult : public CGameState
{

};