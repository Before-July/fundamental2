#include "raylib.h"
#include <random>
#include <float.h>
#include <vector>

#include "Game.h"
#include "Rectengle.h"
#include "Circle.h"
#include "Triangle.h"
#include "Sakura.h"
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
    // Fill the array of shapes
    NewShape[0] = new CRectengle();
    NewShape[1] = new CCircle();
    NewShape[2] = new CTriangle();
    NewShape[3] = new CSakura();
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
    Player->update();

    for (auto value : AddShapes)
    {
        value->breathingScale();
    }
    for (auto value: NewShape)
    {
        value->breathingScale();
    }
}

void CGame::draw()
{
    ClearBackground( WHITE );

    char buffer[64];
    snprintf( buffer, sizeof(buffer), "Ball Pos: %0.0f, %0.0f", Ball->getPosition().X, Ball->getPosition().Y );
    

    if( Ball->isActive() )
    {
        //Ball->draw(); //hide temporary
    }

    //Player->draw(); // hide temporary

    // draw shapes

    for (auto value : AddShapes)
    {
        value->draw();
    }
    if (WhichShape < 4)
    {
        NewShape[WhichShape]->draw();
    }
    DrawText(TextFormat("Shape: %d", AddShapes.size()), 5, 5, 40, DARKGRAY); // TextFormat here as const char* that DrawText can read
}

void CGame::onKey(int keyCode, KeyState keyState)
{
    if( keyCode == 'R' && keyState == KeyState::Pressed )
    {
        reset();
        // clear up the shape vector
        AddShapes.clear();
    }

    // Send key events to the ball.
    if( Ball->isActive() )
    {
        Ball->onKey( keyCode, keyState );
    }

    // player move left/right
    if (keyCode == KEY_A && keyState == KeyState::Pressed) // move left
    {
        Player->setDirection(-1);
    }
    if (keyCode == KEY_D && keyState == KeyState::Pressed) // move right
    {
        Player->setDirection(1);
    }

    // Switch shape 
    if (keyCode == KEY_ONE && keyState == KeyState::Pressed)
    {
        WhichShape = 0;
        NewShape[WhichShape]->resetScale();
    }
    if (keyCode == KEY_TWO && keyState == KeyState::Pressed)
    {
        WhichShape = 1;
        NewShape[WhichShape]->resetScale();
    }
    if (keyCode == KEY_THREE && keyState == KeyState::Pressed)
    {
        WhichShape = 2;
        NewShape[WhichShape]->resetScale();
    }
    if (keyCode == KEY_FOUR && keyState == KeyState::Pressed)
    {
        WhichShape = 3;
        NewShape[WhichShape]->resetScale();
    }
    if (keyCode == KEY_FIVE && keyState == KeyState::Pressed)
    {
        WhichShape = 4;
    }

    // Add scale
    if (keyCode == KEY_B && keyState == KeyState::Pressed && WhichShape < 4)
    {
        NewShape[WhichShape]->addScale();
    }

}


void CGame::onMouseButton(int button, KeyState keyState)
{
    // click mouse to add shape
    if (button==MouseButton::MOUSE_BUTTON_LEFT&& keyState==KeyState::Pressed)
    {
        if (WhichShape == 0)
        {
            CShape* add = new CRectengle();
            *add = *NewShape[WhichShape];
            AddShapes.push_back(add);
        }
        else if (WhichShape == 1)
        {
            CShape* add = new CCircle();
            *add = *NewShape[WhichShape];
            AddShapes.push_back(add);
        }
        else if (WhichShape == 2)
        {
            CShape* add = new CTriangle();
            *add = *NewShape[WhichShape];
            AddShapes.push_back(add);
        }
        else if (WhichShape == 3)
        {
            CShape* add = new CSakura();
            *add = *NewShape[WhichShape];
            AddShapes.push_back(add);
        }
    }
   
}

void CGame::onMouseMove(float x, float y)
{
    if (WhichShape < 4)
    {
        NewShape[WhichShape]->setPosition(x, y);
    }
    
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
