#include "Bullet.h"


CBullet::CBullet(vec2 position) : Position(position)
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

void CBullet::update(float deltaTime)
{
    Position.Y += VelocityY * deltaTime;
}



vec2 CBullet::getPosition()
{
    return Position;
}

