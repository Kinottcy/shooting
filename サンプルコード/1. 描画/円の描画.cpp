#include "Game.hpp"

void Start()
{
}

void Update()
{
    Clear(Color::darkgray);
    
    // 円の塗りつぶし
    FillCircle({0, 0}, 100.0f, Color::lightcyan);
    
    // 円の枠線の描画
    DrawCircle({0, 0}, 100.0f, 3.0f, Color::darkcyan);
}

