#include "Game.hpp"

void Start()
{
}

void Update()
{
    Clear(Color::darkgray);
    
    // 三角形の塗りつぶし
    FillTriangle({0, 0}, {100, 0}, {50, 100}, Color::yellow);
    
    // 三角形の枠線の描画
    DrawTriangle({0, 0}, {100, 0}, {50, 100}, 3.0f, Color::darkyellow);
    
    // 複数の色を指定しての描画
    SetModelTranslation(-100, -100);
    FillTriangle({0, 0}, {100, 0}, {50, 100}, Color::yellow, Color::red, Color::green);
    DrawTriangle({0, 0}, {100, 0}, {50, 100}, 3.0f, Color::white, Color::blue, Color::orange);
}

