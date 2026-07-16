#include "Rectengle.h"

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

