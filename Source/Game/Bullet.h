#pragma once
#include "Helpers/Vector.h"
#include "Helpers/Sprite2D.h"
#include <vector>
#include <string>

class Sprite2D;

class CBullet
{
public:
	CBullet();
	~CBullet();

	void draw();
	void update(float deltaTime);
	vec2 getPosition();

	void set_shooting_position(vec2 position);
	void set_Is_shooting(bool is_shooting);
	bool get_Is_shooting() const;
private:
	vec2 Position;
	float VelocityY = -400.0f;

	float Angles = 0.0f;
	vec2 Scale = 3;

	Texture2D Texture;
	Sprite2D* Sprite;
	std::vector<Sprite2D*> Animation;

	std::string PathName;
	float Animation_timer = 0.0f;
	float Animation_fPS = 3.0f;
	int Frame_count = 0;

	bool Is_shooting = false;
};