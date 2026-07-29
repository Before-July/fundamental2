#pragma once

#include "raylib.h"
#include "Helpers/Vector.h"


class CShape
{
public:
    CShape();
    ~CShape();
    virtual void draw() = 0;
    void setPosition(float mouseX, float mouseY);
    void addScale();
    void resetScale();
    void breathingScale();
    

protected:
    vec2 Position;
    float Angles = 0.0f;
    vec2 Scale = 1;
    vec2 Breathing;
    double AddBreath = 0.0;

    Color ObjectColor;
};


class CSakura : public CShape
{
public:

    CSakura();
    ~CSakura();
    void draw() override;


private:

    vec2 setRoundPosition(float radius, double angle);

};


class CRectengle : public CShape
{
public:
    CRectengle();
    //CRectengle(float x, float y, float scale);
    ~CRectengle();
    void draw() override;

private:
    float Height;
    float Width;
};


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


class CCircle : public CShape
{
public:
    CCircle();
    ~CCircle();
    void draw() override;

private:
    float Radius;
};
