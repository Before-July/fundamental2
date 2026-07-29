#include "StampsGame.h"

CStampsGame::CStampsGame()
{
    // Fill the array of shapes
    NewShape[0] = new CRectengle();
    NewShape[1] = new CCircle();
    NewShape[2] = new CTriangle();
    NewShape[3] = new CSakura();
    // fill the array to show shapes
    ShowShape[0] = new CRectengle();
    ShowShape[1] = new CCircle();
    ShowShape[2] = new CTriangle();
    ShowShape[3] = new CSakura();
    ShowShape[0]->setPosition(50, 200);
    ShowShape[1]->setPosition(200, 200);
    ShowShape[2]->setPosition(300, 200);
    ShowShape[3]->setPosition(500, 200);
}

CStampsGame::~CStampsGame()
{
    for (auto value : ShowShape)
    {
        delete value;
        value = nullptr;
    }
    for (auto value : AddShapes)
    {
        delete value;
        value = nullptr;
    }
    for (auto value : NewShape)
    {
        delete value;
        value = nullptr;
    }
}

void CStampsGame::update(float deltaTime)
{
    for (auto value : ShowShape)
    {
        value->breathingScale();
    }
    for (auto value : AddShapes)
    {
        value->breathingScale();
    }
    for (auto value : NewShape)
    {
        value->breathingScale();
    }
}


void CStampsGame::draw()
{
    ClearBackground(WHITE);

    // draw shapes
    for (auto value : ShowShape)
    {
        value->draw();
    }
    for (auto value : AddShapes)
    {
        value->draw();
    }
    if (WhichShape < 4)
    {
        NewShape[WhichShape]->draw();
    }
    DrawText(TextFormat("Shape: %d", AddShapes.size()), 5, 5, 40, DARKGRAY); // TextFormat here as const char* that DrawText can read
}


void CStampsGame::onKey(int keyCode, KeyState keyState)
{
    if (keyCode == 'R' && keyState == KeyState::Pressed)
    {
        // clear up the shape vector
        AddShapes.clear();
    }

    // Switch shape 
    if (keyCode == KEY_ONE && keyState == KeyState::Pressed)
    {
        WhichShape = 0;
        NewShape[WhichShape]->resetScale();
    }
    if (keyCode == KEY_TWO && keyState == KeyState::Pressed)
    {
        WhichShape = 1;
        NewShape[WhichShape]->resetScale();
    }
    if (keyCode == KEY_THREE && keyState == KeyState::Pressed)
    {
        WhichShape = 2;
        NewShape[WhichShape]->resetScale();
    }
    if (keyCode == KEY_FOUR && keyState == KeyState::Pressed)
    {
        WhichShape = 3;
        NewShape[WhichShape]->resetScale();
    }
    if (keyCode == KEY_FIVE && keyState == KeyState::Pressed)
    {
        WhichShape = 4;
    }

    // Add scale
    if (keyCode == KEY_B && keyState == KeyState::Pressed && WhichShape < 4)
    {
        NewShape[WhichShape]->addScale();
    }

}


void CStampsGame::onMouseButton(int button, KeyState keyState)
{
    // click mouse to add shape
    if (button == MouseButton::MOUSE_BUTTON_LEFT && keyState == KeyState::Pressed)
    {
        if (WhichShape == 0)
        {
            CShape* add = new CRectengle();
            *add = *NewShape[WhichShape];
            AddShapes.push_back(add);
        }
        else if (WhichShape == 1)
        {
            CShape* add = new CCircle();
            *add = *NewShape[WhichShape];
            AddShapes.push_back(add);
        }
        else if (WhichShape == 2)
        {
            CShape* add = new CTriangle();
            *add = *NewShape[WhichShape];
            AddShapes.push_back(add);
        }
        else if (WhichShape == 3)
        {
            CShape* add = new CSakura();
            *add = *NewShape[WhichShape];
            AddShapes.push_back(add);
        }
    }

}


void CStampsGame::onMouseMove(float x, float y)
{
    if (WhichShape < 4)
    {
        NewShape[WhichShape]->setPosition(x, y);
    }

}