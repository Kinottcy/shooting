#include "Game.hpp"


Color colors[6];


void Start()
{
    colors[0] = Color::darkgreen;
    colors[1] = Color::lightgreen;
    colors[2] = Color::darkred;
    colors[3] = Color::lightred;
    colors[4] = Color::darkblue;
    colors[5] = Color::lightblue;
}

void DrawBall(int type, const Vector2& pos)
{
    for (int i = 0; i < 5; i++) {
        float a = i / 4.0f;
        FillCircle(Vector2(pos.x-i*2, pos.y+i*2), 20-i*4.1f, Color::Lerp(colors[type*2], colors[type*2+1], a));
    }
}

void DrawMarker(const Vector2& pos)
{
    for (int i = 0; i < 6; i++) {
        int b = i / 2;
        DrawLine(Vector2(pos.x+20-i-10, pos.y-b+12), Vector2(pos.x+i-10, pos.y-12+b), Color::white);
        DrawLine(Vector2(pos.x+i-10, pos.y-b+12), Vector2(pos.x+20-i-10, pos.y-12+b), Color::white);
    }
}

void DrawCursor(const Vector2& pos)
{
    DrawRect(Rect(pos.x-20, pos.y-16, 40, 32), Color::white);
    DrawRect(Rect(pos.x-19, pos.y-15, 38, 30), Color::white);
}

void Update()
{
    Clear(Color::black);
    
    SetCameraTranslation(Screen::size()/2);
    
    DrawLine({0, 240}, {640, 240}, Color::gray);
    DrawLine({320, 0}, {320, 480}, Color::gray);
    
    for (int i = 0; i < 3; i++) {
        DrawBall(i, Vector2(320 + (i - 1) * 60, 240));
    }
    //DrawMarker({320, 240});
    DrawCursor({320, 240-40});
}

