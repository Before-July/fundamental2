#pragma once
#include "Helpers/Vector.h"

class CCollision
{
public:
	CCollision();
	~CCollision();

	bool is_colliding(float topLeftX, float topRightX, float topLeftY, float bottomLeftY);
	void drawCollision(Color color);
	void setCollision(vec2 topLeft, vec2 topRight, vec2 bottomLeft, vec2 bottomRight);
	vec2 getCollisionPoint(int whichPoint);

private:
	vec2 TopLeft;
	vec2 TopRight;
	vec2 BottomLeft;
	vec2 BottomRight;

};

