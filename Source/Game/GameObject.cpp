#include "GameObject.h"
#include "Helpers/Drawing.h"

CGameObject::CGameObject()
{
}

CGameObject::~CGameObject()
{
}

vec2 CGameObject::getPosition()
{
    return Position;
}

void CGameObject::setPosition(vec2 position)
{
    Position = position;
}

CPlayer::CPlayer()
{

    Texture = LoadTexture("Data/Textures/Samurai.png");
    Sprite = new Sprite2D(Texture);
}

CPlayer::~CPlayer()
{
    delete Sprite;
    UnloadTexture(Texture);
}

void CPlayer::update()
{
    Position.X += Direction * MoveSpeed;
}

void CPlayer::draw()
{
    Sprite->draw(Position, Angles, Scale);
}

int CPlayer::getSpriteSize()
{
    return Texture.height;
}