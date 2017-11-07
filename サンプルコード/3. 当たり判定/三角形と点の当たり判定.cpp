#include "Game.hpp"

Vector2 p[4];
int dragTarget;

void Start()
{
    p[0] = { -100, -57.74f };   // 三角形の頂点1
    p[1] = { 100, -57.74f };    // 三角形の頂点2
    p[2] = { 0, 115.47f };      // 三角形の頂点3
    p[3] = { 0, 0 };            // 当たり判定を行う点

    dragTarget = -1;
}

// 当たり判定
bool CheckHit(const Vector2& p0, const Vector2& p1, const Vector2& p2, const Vector2& hitPos)
{
    float c0 = Vector2::Cross(p0 - p2, hitPos - p0);
    float c1 = Vector2::Cross(p1 - p0, hitPos - p1);
    float c2 = Vector2::Cross(p2 - p1, hitPos - p2);
    Debug("c0=%.2f", c0);
    Debug("c1=%.2f", c1);
    Debug("c2=%.2f", c2);
    return ((c0 > 0 && c1 > 0 && c2 > 0) || (c0 < 0 && c1 < 0 && c2 < 0));
}

void Update()
{
    // 操作点のドラッグ
    if (dragTarget < 0) {
        if (Input::GetMouseButton(0)) {
            for (int i = 0; i < 4; i++) {
                if (Vector2::Distance(p[i], GetMousePosition()) <= 10.0f) {
                    dragTarget = i;
                    break;
                }
            }
            if (dragTarget < 0) {
                dragTarget = 3;
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

    Debug("[HitTest in Triangle]");
    Debug("Point: (%d, %d)", (int)p[3].x, (int)p[3].y);

    if (CheckHit(p[0], p[1], p[2], p[3])) {
        FillTriangle(p[0], p[1], p[2], Color::lightcyan);
    } else {
        FillTriangle(p[0], p[1], p[2], Color::lightpink);
    }
    DrawTriangle(p[0], p[1], p[2], 2.0f, Color::darkcyan);

    for (int i = 0; i < 3; i++) {
        DrawLine(p[i], p[3], 1.0f, Color::black.Alpha(0.3f));
        FillCircle(p[i], 5.0f, Color::red.Alpha(0.8f));
    }
    FillCircle(p[3], 5.0f, Color::blue.Alpha(0.8f));
}

