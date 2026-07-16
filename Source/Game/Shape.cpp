#include "Shape.h"

CShape::CShape()
{
	ObjectColor = RED;
}

CShape::~CShape()
{
}

void CShape::setPosition(float mouseX, float mouseY)
{
	Position.X = mouseX;
	Position.Y = mouseY;
}

void CShape::addScale() { Scale += 0.1; }

void CShape::resetScale() { Scale = 1; }

void CShape::breathingScale()
{
	AddBreath += 1;
	double breath = AddBreath * (3.14 / 180.0);
	Breathing.X =sin(breath) + Scale.X;
	Breathing.Y =sin(breath) + Scale.Y;
}




