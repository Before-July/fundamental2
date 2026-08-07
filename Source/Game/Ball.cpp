#include "Ball.h"
#include "Game.h"
#include "Helpers/MathFuncs.h"
#include "Helpers/Sprite2D.h"

CBall::CBall(CGame* game)
    : Game( game )
{
    Active = true;

    Radius = 20.0f;
    Scale = 1.0f;

    Sprite = new Sprite2D( Game->getTexture("SoccerBall") );
}

CBall::~CBall()
{
    delete Sprite;
}

void CBall::reset()
{

}

void CBall::update(float deltaTime)
{
    float speed = 200.0f;
    vec2 gravity = { 0.0f, 200.0f };

    vec2 dir = Controls.getNormalized();
    vec2 forces = gravity + dir * speed;

    Velocity += forces * deltaTime;

    Position.X += Velocity.X * deltaTime;
    Position.Y += Velocity.Y * deltaTime;

    Angle += deltaTime * Velocity.X;

    /*if (Velocity.X > 0)
    {
        Angle += deltaTime * 150;
    }
    else
    {
        Angle += deltaTime * (-150);
    }*/
    

    // Lock to edges.
    if (Position.X < 32.0f * Scale.X)
    {
        Position.X = 32.0f * Scale.X;
        Velocity.X *= -0.95f; // Bounce off the left edge.
    }
    if( Position.X >= GetScreenWidth()-32.0f * Scale.X)
    {
        Position.X = GetScreenWidth()-32.0f * Scale.X;
        Velocity.X *= -0.95f; // Bounce off the right edge.
    }
    if( Position.Y < 32.0f * Scale.X)
    {
        Position.Y = 32.0f * Scale.X;
        Velocity.X *= 0.95f; // Slow down horizontal velocity.
        Velocity.Y *= -0.95f; // Bounce off the top.
    }
    if( Position.Y >= GetScreenHeight()-32.0f * Scale.X)
    {
        Position.Y = GetScreenHeight()-32.0f * Scale.X;
        Velocity.X *= 0.95f; // Slow down horizontal velocity.
        Velocity.Y *= -0.95f; // Bounce off the bottom.
    }
}

void CBall::draw()
{
    Sprite->draw( Position, Angle, Scale );
}

