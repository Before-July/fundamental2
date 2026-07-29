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
	AddBreath += 2;
	double breath = AddBreath * (3.14 / 180.0);
	Breathing.X = 0.25 * sin(breath) + Scale.X;
	Breathing.Y = 0.25 * sin(breath) + Scale.Y;
}

CSakura::CSakura()
{
    ObjectColor = RED;
}

CSakura::~CSakura()
{
}

void CSakura::draw()
{
    for (int i = 0; i < 5; i++) // first round of circles
    {
        int angle = (360 / 5) * (i + 1);
        DrawCircle(Position.X + setRoundPosition(50, angle).X * Breathing.X, Position.Y - setRoundPosition(50, angle).Y * Breathing.Y, 40 * Breathing.X, ObjectColor);
    }
    for (int i = 0; i < 5; i++) // second round of circles
    {
        int angle = (360 / 5) * (i + 1);
        DrawCircle(Position.X + setRoundPosition(40, angle).X * Breathing.X, Position.Y - setRoundPosition(40, angle).Y * Breathing.Y, 30 * Breathing.X, WHITE);
    }
    for (int i = 0; i < 5; i++) // round of lines
    {
        int angle = (360 / 5) * (i + 1);
        DrawLine(Position.X, Position.Y, Position.X + setRoundPosition(40, angle).X * Breathing.X, Position.Y - setRoundPosition(40, angle).Y * Breathing.Y, ObjectColor);
    }
    for (int i = 0; i < 5; i++) // third round of circle
    {
        int angle = (360 / 5) * (i + 1);
        DrawCircle(Position.X + setRoundPosition(40, angle).X * Breathing.X, Position.Y - setRoundPosition(40, angle).Y * Breathing.Y, 5 * Breathing.X, ObjectColor);
    }
    DrawCircle(Position.X, Position.Y, 20 * Breathing.X, ObjectColor);// center circle
    DrawRectangle(Position.X - 2.5 * Breathing.X, Position.Y - 10 * Breathing.Y, 5 * Breathing.X, 20 * Breathing.Y, WHITE);
    DrawRectangle(Position.X - 10 * Breathing.X, Position.Y - 2.5 * Breathing.Y, 20 * Breathing.X, 5 * Breathing.Y, WHITE);
}

vec2 CSakura::setRoundPosition(float radius, double angle)
{
    vec2 position;
    double roundAngle = angle * (3.14 / 180.0); ////
    position.X = radius * std::cos(roundAngle);
    position.Y = radius * std::sin(roundAngle);
    return position;
}

CRectengle::CRectengle() : Width(40.0), Height(60.0)
{
    ObjectColor = BLUE;
}

CRectengle::~CRectengle()
{
}

void CRectengle::draw() // draw rectengle
{
    DrawRectangle(Position.X - Width / 2, Position.Y - Height / 2, Width * Breathing.X, Height * Breathing.Y, ObjectColor);
}

CTriangle::CTriangle()
{
    ObjectColor = GREEN;
}

CTriangle::~CTriangle()
{
}

void CTriangle::draw()
{
    DrawLine(Position.X, Position.Y, Position.X + v1.X * Breathing.X, Position.Y + v1.Y * Breathing.Y, ObjectColor);
    DrawLine(Position.X, Position.Y, Position.X + Breathing.X * setTrianglePoint(v1.X, 60).X, Position.Y + Breathing.Y * setTrianglePoint(v1.X, 60).Y, ObjectColor);
    DrawLine(Position.X + Breathing.X * setTrianglePoint(v1.X, 60).X, Position.Y + Breathing.Y * setTrianglePoint(v1.X, 60).Y, Position.X + v1.X * Breathing.X, Position.Y + v1.Y * Breathing.Y, ObjectColor);

}

vec2 CTriangle::setTrianglePoint(float length, float angle)
{
    vec2 position;
    double roundAngle = angle * (3.14 / 180.0);
    position.X = length * std::cos(roundAngle);
    position.Y = length * std::sin(roundAngle);
    return position;

}

CCircle::CCircle() : Radius(50.0f)
{
    ObjectColor = RED;
}

CCircle::~CCircle()
{
}

void CCircle::draw()
{
    DrawCircle(Position.X, Position.Y, Radius * Breathing.X, ObjectColor);
}