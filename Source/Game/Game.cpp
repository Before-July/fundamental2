#include "raylib.h"
#include <random>
#include <float.h>
#include <vector>

#include "Game.h"
#include "Helpers/MathFuncs.h"
#include "Helpers/Sprite2D.h"

CGame::CGame()
{
    std::random_device rd;
    srand( rd() );

    Textures["SoccerBall"] = LoadTexture( "Data/Textures/SoccerBall.png" );

    // Create a ball.
    for (int i = 0; i < num_MaxBalls; i++)
    {
        CBall* ball = new CBall(this);
        BallPool.push_back(ball);
    }
    for (int i = 0; i < 6; i++)
    {
        float positionX = randFloat(50.0f, (GetScreenWidth() - 50.0f));
        spawnBall(vec2(positionX, 150), vec2(300, -300));
    }
    

    // Create a player.
    Player = new CPlayer;   
    Player->setPosition({ GetScreenWidth() / 2.0f , GetScreenHeight() - Player->getSpriteSize() * 2.0f });



    reset();
}

CGame::~CGame()
{
    for (auto value: BallPool)
    {
        delete value;
        value = nullptr;
    }
    for (auto value: ActiveBall)
    {
        delete value;
        value = nullptr;
    }
    delete Player;

    for( auto texturePair : Textures )
    {
        UnloadTexture( texturePair.second );
    }
}

void CGame::reset()
{
    //Ball->reset();
    //Ball->setPosition( { GetScreenWidth()/2.0f + rand() % 100 - 50, GetScreenHeight()/2.0f + rand() % 20 - 10 } );
    //Ball->setVelocity( {randFloat(-200, 200), randFloat(-200, 200)} );
}

void CGame::update(float deltaTime)
{

    Player->update( deltaTime );
    
    for (auto value : ActiveBall)
    {
        value->update(deltaTime);
    }
    if (bullet != nullptr)
    {
        bullet->update(deltaTime);
    }

}

void CGame::draw()
{
    ClearBackground( WHITE );

    //char buffer[64];
    //snprintf( buffer, sizeof(buffer), "Ball Pos: %0.0f, %0.0f", Ball->getPosition().X, Ball->getPosition().Y );
    
    Player->draw();

    for (auto value : ActiveBall)
    {
        value->draw();
    }
    if (bullet != nullptr)
    {
        bullet->draw();
    }
}

void CGame::onKey(int keyCode, KeyState keyState)
{
    if( keyCode == 'R' && keyState == KeyState::Pressed )
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
        bullet = new CBullet(Player->getPosition());
    }
}


void CGame::onMouseButton(int button, KeyState keyState)
{
    
}

void CGame::onMouseMove(float x, float y)
{
    
}

CBall* CGame::spawnBall(vec2 position, vec2 velocity)
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

Texture2D CGame::getTexture(const char* textureName) const
{
    auto it = Textures.find( textureName );
    if( it != Textures.end() )
    {
        return it->second;
    }

    // Return an empty texture if not found.
    assert( false );
    return Texture2D();
}

