#include "Collision.h"
#include "raylib.h"

CCollision::CCollision()
{
}

CCollision::~CCollision()
{
}

bool CCollision::is_colliding(float topLeftX, float topRightX, float topLeftY, float bottomLeftY)
{
	if (TopLeft.X > topRightX || TopRight.X < topLeftX || TopLeft.Y > bottomLeftY || BottomLeft.Y < topLeftY)
	{
		return false;
	}

	return true;
}

void CCollision::drawCollision(Color color)
{
	DrawLineEx(TopLeft, TopRight, 3.0, color);
	DrawLineEx(TopLeft, BottomLeft, 3.0, color);
	DrawLineEx(TopRight,BottomRight , 3.0, color);
	DrawLineEx(BottomLeft, BottomRight, 3.0, color);
}

void CCollision::setCollision(vec2 topLeft, vec2 topRight, vec2 bottomLeft, vec2 bottomRight)
{
	TopLeft = topLeft;
	TopRight = topRight;
	BottomLeft = bottomLeft;
	BottomRight = bottomRight;
}

vec2 CCollision::getCollisionPoint(int whichPoint)
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

