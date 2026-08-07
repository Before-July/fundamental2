#pragma once
#include "Helpers/Vector.h"
#include "Helpers/Sprite2D.h"
#include <vector>
#include <string>

class Sprite2D;

class CBullet
{
public:
	CBullet(vec2 postion);
	~CBullet();

	void draw();
	void update(float deltaTime);
	vec2 getPosition();


private:
	vec2 Position;
	float VelocityY = -400.0f;

	float Angles = 0.0f;
	vec2 Scale = 2;


	Texture2D Texture;
	Sprite2D* Sprite;
	std::vector<Sprite2D*> Animation;

	std::string PathName;
	float Animation_timer = 0.0f;
	float Animation_fPS = 3.0f;
	int Frame_count = 0;
};