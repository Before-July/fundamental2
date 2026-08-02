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
        loadAnimation("run", 4, 15.0);
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


CFloor::CFloor()
{
    Position.X = GetScreenWidth() / 2.0;
    Position.Y = GetScreenHeight();
    TopLeft = vec2(0.0, GetScreenHeight() - 10.0);
    TopRight = vec2(GetScreenWidth(), GetScreenHeight() - 10.0);
    BottomLeft = vec2(0.0, GetScreenHeight());
    BottomRight = vec2(GetScreenWidth(), GetScreenHeight());
    Collision = new CCollision();
    Collision->setCollision(TopLeft, TopRight, BottomLeft, BottomRight);
}

CFloor::~CFloor()
{
}

vec2 CFloor::getPoint(int whichPoint)
{
    switch (whichPoint)
    {
    case 1:
        return TopLeft;
        break;
    case 2:
        return TopRight;
        break;
    case 3:
        return BottomLeft;
        break;
    case 4:
        return BottomRight;
        break;
    default:
        break;
    }
    return vec2();
}


void CFloor::draw()
{
    DrawRectangle(0.0, GetScreenHeight() - 10, GetScreenWidth(), 10, BLUE);
    Collision->drawCollision(RED);
}
