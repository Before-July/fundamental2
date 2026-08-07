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

void CCollision::setCollision(vec2 center, float width, float hight)
{
	TopLeft = { (center.X - width / 2.0f), (center.Y - hight / 2.0f) };
	TopRight = { (center.X + width / 2.0f), (center.Y - hight / 2.0f) };
	BottomLeft = { (center.X - width / 2.0f), (center.Y + hight / 2.0f) };
	BottomRight = { (center.X + width / 2.0f), (center.Y + hight / 2.0f) };
}

vec2 CCollision::getCollisionPoint(int whichPoint) const
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

