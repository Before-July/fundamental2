#pragma once
#include "Helpers/Vector.h"

class CCollision
{
public:
	CCollision();
	~CCollision();

	bool is_colliding(float topLeftX, float topRightX, float topLeftY, float bottomLeftY);
	void drawCollision(Color color);
	void setCollision(vec2 center, float width, float hight);
	vec2 getCollisionPoint(int whichPoint) const;

private:
	vec2 TopLeft;
	vec2 TopRight;
	vec2 BottomLeft;
	vec2 BottomRight;

};

