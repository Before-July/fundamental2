#include "GameObject.h"
#include "Helpers/Drawing.h"
#include "Helpers/MathFuncs.h"


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
    if (keyCode == KEY_K && keyState == KeyState::Pressed)
    {
        CanDash = true;
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
    if (Direction != 0)
    {
        faceDirection.X = Direction;
    }
    if (Is_attacking)
    {
        attack(deltaTime);
        
    }
    else
    {
        AttackTimer = 0.0f;
        if (Direction == 0)
        {
            loadAnimation("idle", 4, 3.0f);
        }
        else
        {
            loadAnimation("run", 4, 15.0f);
            if (faceDirection.X < 0)
            {
                flip = true;
            }
            else
            {
                flip = false;
            }
        }
        if (Position.X < 11.0f * Scale.X)
        {
            Position.X = 11.0f * Scale.X;
        }
        else if (Position.X >= GetScreenWidth() - 11.0f * Scale.X)
        {
            Position.X = GetScreenWidth() - 11.0f * Scale.X;
        }
        if (CanDash && DashTimer > 0.0f)
        {
            Position.X += faceDirection.X * DashSpeed * deltaTime;
            DashTimer -= deltaTime;
            loadAnimation("run", 4, 15.0f);
            if (DashTimer <= 0.0f) // finish dash
            {
                CanDash = false;
                DashCoolDownTimer = 0.3f;
            }
        }
        else
        {
            Position.X += Direction * MoveSpeed * deltaTime;
            DashCoolDownTimer -= deltaTime;
            if (DashCoolDownTimer < 0.0f)
            {
                DashTimer = 0.1f;
                DashCoolDownTimer = 0.0f;
            }
        }
    }

}

void CPlayer::draw()
{
    AnimationTimer = AnimationTimer + 1 / 60.0f;
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
    if (Ani_name != ani_name)
    {
        Ani_name = ani_name;
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
    
}

void CPlayer::attack(float deltaTime)
{
    loadAnimation("attack", 4, 4.0f);
    AttackTimer += deltaTime;
    if (AttackTimer > 0.6f)
    {
        Is_attacking = false;
    }
}

void CPlayer::set_is_attacking(bool is_attacking)
{
    Is_attacking = is_attacking;
}

bool CPlayer::get_is_attacking()
{
    return Is_attacking;
}


CBlock::CBlock(vec2 posistion, float width, float hight) :
    Position(posistion), Width(width), Hight(hight)
{
    Collision = new CCollision();
    Collision->setCollision(Position, Width, Hight);
}

CBlock::~CBlock()
{
}


void CBlock::draw() // upload texture to draw
{
    
}
