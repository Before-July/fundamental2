#include "Bullet.h"


CBullet::CBullet()
{
	for (int i = 0; i < 2; i++)
	{
		PathName = "Data/Textures/bullet" + std::to_string(i) + ".png";
		Texture = LoadTexture(PathName.c_str());
		Sprite = new Sprite2D(Texture);
		Animation.push_back(Sprite);
	}

}

CBullet::~CBullet()
{
}



void CBullet::draw()
{
    if (Is_shooting)
    {
        Animation_timer = Animation_timer + (1 / 60.0f);
        if (Animation_timer >= 1 / Animation_fPS)
        {
            Frame_count += 1;
            Animation_timer = 0.0f;
        }

        //Sprite->draw(Position, Angles, Scale);
        if (Frame_count == Animation.size())
        {
            Frame_count = 0;
        }

        Animation[Frame_count]->draw(Position, Angles, Scale);
    }
    
}

void CBullet::update(float deltaTime)
{
    if (Is_shooting)
    {
        Position.Y += VelocityY * deltaTime;
    }
   
}



vec2 CBullet::getPosition()
{
    return Position;
}

void CBullet::set_shooting_position(vec2 position)
{
    Position = position;
}

void CBullet::set_Is_shooting(bool is_shooting)
{
    Is_shooting = is_shooting;
}

bool CBullet::get_Is_shooting() const
{
    return Is_shooting;
}

