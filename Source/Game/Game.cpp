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
    Ball = new CBall(this);
    // Create a player.
    Player = new CPlayer;   
    Player->setPosition({ GetScreenWidth() / 2.0f , GetScreenHeight() - Player->getSpriteSize() * 2.0f });

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

    Player->draw();

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

