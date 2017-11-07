#include "Game.hpp"

Vector2 p[3];
int dragTarget;

void Start()
{
    p[0] = { -150, -100 };  // 矩形の左下の頂点
    p[1] = { 50, 50 };      // 矩形の右上の頂点
    p[2] = { -75, -50 };    // 当たり判定を行う点

    dragTarget = -1;
}

void Update()
{
    // 操作点のドラッグ
    if (dragTarget < 0) {
        if (Input::GetMouseButton(0)) {
            for (int i = 0; i < 3; i++) {
                if (Vector2::Distance(p[i], GetMousePosition()) <= 10.0f) {
                    dragTarget = i;
                    break;
                }
            }
            if (dragTarget < 0) {
                dragTarget = 2;
            }
        }
    } else {
        if (Input::GetMouseButton(0)) {
            p[dragTarget] = GetMousePosition();
        } else {
            dragTarget = -1;
        }
    }

    // 画面の描画
    Clear(Color::gray);

    Debug("[HitTest between Rect & Point]");

    float minX = std::min(p[0].x, p[1].x);
    float minY = std::min(p[0].y, p[1].y);
    float maxX = std::max(p[0].x, p[1].x);
    float maxY = std::max(p[0].y, p[1].y);
    Rect rect(minX, minY, maxX - minX, maxY - minY);

    if (rect.Contains(p[2])) {
        FillRect(rect, Color::lightcyan);
    } else {
        FillRect(rect, Color::lightpink);
    }
    DrawRect(rect, 3.0f, Color::darkcyan);

    FillCircle(p[0], 5.0f, Color::orange);
    FillCircle(p[1], 5.0f, Color::orange);
    FillCircle(p[2], 5.0f, Color::blue.Alpha(0.75f));
}

