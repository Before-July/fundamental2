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

    // Create floor
    Floor = new CFloor();


    // Create a ball.
    Ball = new CBall(this);
    // Create a player.
    Player = new CPlayer;   
    Player->setPosition({ GetScreenWidth() / 2.0f , GetScreenHeight() - Player->getSpriteSize() * 2.0f });
    PlayerCollision = new CCollision();


    reset();
}

CGame::~CGame()
{
    delete Ball;
    delete Player;

    for( auto texturePair : Textures )
    {
        UnloadTexture( texturePair.second );
    }
}

void CGame::reset()
{
    Ball->reset();
    Ball->setActive( true );
    Ball->setPosition( { GetScreenWidth()/2.0f + rand() % 100 - 50, GetScreenHeight()/2.0f + rand() % 20 - 10 } );
    Ball->setVelocity( {randFloat(-200, 200), randFloat(-200, 200)} );
}

void CGame::update(float deltaTime)
{
    Ball->update( deltaTime );
    Player->update( deltaTime );
    PlayerCollision->setCollision
    (
        { (Player->getPosition().X - 30),(Player->getPosition().Y - 60)},
        { (Player->getPosition().X + 30),(Player->getPosition().Y - 60) },
        { (Player->getPosition().X - 30),(Player->getPosition().Y + 64) },
        { (Player->getPosition().X + 30),(Player->getPosition().Y + 64) }
    );

}

void CGame::draw()
{
    ClearBackground( WHITE );

    char buffer[64];
    snprintf( buffer, sizeof(buffer), "Ball Pos: %0.0f, %0.0f", Ball->getPosition().X, Ball->getPosition().Y );
    

    if( Ball->isActive() )
    {
        Ball->draw(); 
    }
    Floor->draw();
    Player->draw();
    if (PlayerCollision->is_colliding(Floor->getPoint(1).X,Floor->getPoint(2).X,Floor->getPoint(1).Y,Floor->getPoint(3).Y))
    {
        PlayerCollision->drawCollision(RED);
    }
    else
    {
        PlayerCollision->drawCollision(GREEN);
    }
    
}

void CGame::onKey(int keyCode, KeyState keyState)
{
    if( keyCode == 'R' && keyState == KeyState::Pressed )
    {
        reset();
    }

    // Send key events to the ball.
    if( Ball->isActive() )
    {
        Ball->onKey( keyCode, keyState );
    }
    Player->onKey(keyCode, keyState);
}


void CGame::onMouseButton(int button, KeyState keyState)
{
    
}

void CGame::onMouseMove(float x, float y)
{
    
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

