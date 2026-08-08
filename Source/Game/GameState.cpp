#include "GameState.h"
#include <random>
#include <float.h>
#include <vector>

#include "Game.h"
#include "Helpers/MathFuncs.h"
#include "Helpers/Sprite2D.h"

CGameState::CGameState()
{
}

CGameState::~CGameState()
{
}

CGamePlay::CGamePlay()
{
    std::random_device rd;
    srand(rd());

    Textures["SoccerBall"] = LoadTexture("Data/Textures/SoccerBall.png");

    // Create a ball.
    for (int i = 0; i < num_MaxBalls; i++)
    {
        CBall* ball = new CBall(this);
        BallPool.push_back(ball);
    }



    // Create a player.
    Player = new CPlayer;
    Player->setPosition({ GetScreenWidth() / 2.0f , GetScreenHeight() - Player->getSpriteSize() * 2.0f });

    for (int i = 0; i < num_bullet; i++)
    {
        CBullet* addbullet = new CBullet;
        Bullet.push_back(addbullet);
    }

    reset();
}

CGamePlay::~CGamePlay()
{
    for (auto value : BallPool)
    {
        delete value;
        value = nullptr;
    }
    for (auto value : ActiveBall)
    {
        delete value;
        value = nullptr;
    }
    delete Player;
    Player = nullptr;

    for (auto texturePair : Textures)
    {
        UnloadTexture(texturePair.second);
    }

    for (auto value : Bullet)
    {
        delete value;
        value = nullptr;
    }
}

void CGamePlay::reset()
{
    for (auto ball : ActiveBall)
    {
        BallPool.push_back(ball);
    }
    ActiveBall.clear();
    for (int i = 0; i < 6; i++)
    {
        float positionX = randFloat(50.0f, (GetScreenWidth() - 50.0f));
        spawnBall(vec2(positionX, 150), vec2(300, -300));
    }
}

void CGamePlay::update(float deltaTime)
{
    Player->update(deltaTime);

    for (auto value : ActiveBall)
    {
        value->update(deltaTime);
    }
    //if (bullet != nullptr)
    //{
    //    bullet->update(deltaTime);
    //}
    for (auto bullet : Bullet)
    {
        if (bullet->get_Is_shooting())
        {
            bullet->update(deltaTime);
        }
        if (bullet->getPosition().Y < -64.0f)
        {
            bullet->set_Is_shooting(false);
        }
    }
}

void CGamePlay::draw()
{
    ClearBackground(WHITE);

    //char buffer[64];
    //snprintf( buffer, sizeof(buffer), "Ball Pos: %0.0f, %0.0f", Ball->getPosition().X, Ball->getPosition().Y );

    Player->draw();

    for (auto value : ActiveBall)
    {
        value->draw();
    }
    //if (bullet != nullptr)
    //{
    //    bullet->draw();
    //}
    for (auto bullet : Bullet)
    {
        if (bullet->get_Is_shooting())
        {
            bullet->draw();
        }
    }
}

void CGamePlay::onKey(int keyCode, KeyState keyState)
{
    if (keyCode == 'R' && keyState == KeyState::Pressed)
    {
        reset();
    }

    // Send key events to the ball.
    //if( Ball->isActive() )
    //{
    //    Ball->onKey( keyCode, keyState );
    //}
    Player->onKey(keyCode, keyState);

    if (keyCode == KEY_J && keyState == KeyState::Pressed)
    {
        //bullet = new CBullet(Player->getPosition());
        for (auto bullet : Bullet)
        {
            if (!bullet->get_Is_shooting() && !Player->get_is_attacking())
            {
                Player->set_is_attacking(true);
                bullet->set_shooting_position(Player->getPosition());
                bullet->set_Is_shooting(true);
                break;
            }

        }
    }
}

void CGamePlay::onMouseButton(int button, KeyState keyState)
{
}

void CGamePlay::onMouseMove(float x, float y)
{
}

CBall* CGamePlay::spawnBall(vec2 position, vec2 velocity)
{

    if (BallPool.empty())
    {
        return nullptr;
    }

    // Activate 1 ball.
    CBall* ball = BallPool.back();
    BallPool.pop_back();
    ActiveBall.push_back(ball);

    ball->setPosition(position);
    ball->setVelocity(velocity);

    return ball;
}

Texture2D CGamePlay::getTexture(const char* textureName) const
{
    auto it = Textures.find(textureName);
    if (it != Textures.end())
    {
        return it->second;
    }

    // Return an empty texture if not found.
    assert(false);
    return Texture2D();
}
