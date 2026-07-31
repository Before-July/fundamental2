#include "GameObject.h"
#include "Helpers/Drawing.h"


CGameObject::CGameObject()
{
}

CGameObject::~CGameObject()
{
}

void CGameObject::onKey(int keyCode, KeyState keyState)
{
    // player move left/right
    if (keyCode == KEY_A && keyState == KeyState::Pressed) // move left
    {
        Direction--;
    }
    if (keyCode == KEY_D && keyState == KeyState::Pressed) // move right
    {
        Direction++;
    }
    if(keyCode == KEY_A && keyState == KeyState::Released) // stop move left
    {
        Direction++;
    }
    if(keyCode == KEY_D && keyState == KeyState::Released) // stop move right
    {
        Direction--;
    }
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

void CPlayer::update(float deltaTime)
{
    vec2 directionVec = { Direction, 0 };
    directionVec.normalize();
    Position.X += directionVec.X * MoveSpeed * deltaTime;
    if(directionVec.X == 0)
    {
        loadAnimation("idle", 4, 3.0);
    }
    else
    {
        loadAnimation("run", 4, 10.0);
        if(directionVec.X < 0 )
        {
            flip = true;
        }
        else
        {
            flip = false;
        }
    }
}

void CPlayer::draw()
{
    AnimationTimer = AnimationTimer + 1 / 60.0;
    if (AnimationTimer >= 1 / AnimationFPS)
    {
        FrameCount += 1;
        AnimationTimer = 0.0f;
    }
    
    //Sprite->draw(Position, Angles, Scale);
    if (FrameCount == Animation.size())
    {
        FrameCount = 0;
    }

    Animation[FrameCount]->draw(Position, Angles, Scale, flip);
    
}

int CPlayer::getSpriteSize()
{
    return Texture.height;
}

void CPlayer::loadAnimation(std::string ani_name, int num_frame, float fps)
{
    AnimationFPS = fps;
    if (Animation.size() > 0)
    {
        for (auto frame : Animation)
        {
            delete frame;
        }
        Animation.clear();
    }
    for (int i = 0; i < num_frame; i++)
    {
        std::string frame_path = "Data/Textures/" + ani_name + std::to_string(i) + ".png";
        Texture2D loadFrame = LoadTexture(frame_path.c_str());
        Sprite2D* frameSprite = new Sprite2D(loadFrame);
        Animation.push_back(frameSprite);
    }
    
}