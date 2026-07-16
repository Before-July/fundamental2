#pragma once
#include "Shape.h"

class CTriangle : public CShape
{
public:
	CTriangle();
	~CTriangle();
	void draw() override;
	

private:
	vec2 setTrianglePoint(float length, float angle);

	vec2 v1 = { 50,0 };
};

