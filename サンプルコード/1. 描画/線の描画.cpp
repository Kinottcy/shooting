#include "Game.hpp"

void Start()
{
}

void Update()
{
    Clear(Color::darkgray);
    
    // 単色での線の描画
    DrawLine({-150, 60}, {150, 60}, 3.0f, Color::yellow);
    
    // 2色のグラデーションでの線の描画
    DrawLine({-150, -60}, {150, -60}, 10.0f, Color::yellow, Color::red);
}

