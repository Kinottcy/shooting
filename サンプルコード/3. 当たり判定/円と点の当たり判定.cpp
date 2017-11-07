#include "Game.hpp"

Vector2 p[3];
float dx;
int dragTarget;

void Start()
{
    p[0] = { 0, 0 };    // 円の中心点
    p[1] = { 100, 0 };  // 円の右端の点
    p[2] = { 0, -50 };  // 当たり判定を行う点

    dragTarget = -1;
}

/// 円と点の当たり判定
bool CheckHit(const Vector2& center, float radius, const Vector2& hitPos)
{
    //return (Vector2::Distance(hitPos, center) <= radius);
    return ((hitPos - center).SqrMagnitude() <= radius * radius);
}

void Update()
{
    // 操作点のドラッグ
    if (dragTarget < 0) {
        if (Input::GetMouseButton(0)) {
            for (int i = 0; i < 2; i++) {
                if (Vector2::Distance(p[i], GetMousePosition()) <= 10.0f) {
                    dragTarget = i;
                    if (dragTarget == 0) {
                        dx = p[1].x - p[0].x;
                    }
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
            if (dragTarget == 0) {
                p[1].x = p[0].x + dx;
                p[1].y = p[0].y;
            } else if (dragTarget == 1) {
                p[1].y = p[0].y;
            }
        } else {
            dragTarget = -1;
        }
    }

    // 画面の描画
    Clear(Color::gray);

    Debug("[HitTest in Circle]");
    Debug("Point: (%d, %d)", (int)p[2].x, (int)p[2].y);

    float radius = Vector2::Distance(p[0], p[1]);
    Debug("Radius: %.1f", radius);

    if (CheckHit(p[0], radius, p[2])) {
        FillCircle(p[0], radius, Color::lightcyan);
    } else {
        FillCircle(p[0], radius, Color::lightpink);
    }
    DrawCircle(p[0], radius, 3.0f, Color::darkcyan);
    DrawLine(p[0], p[1], 1.0f, Color::black.Alpha(0.3f));

    FillCircle(p[0], 5.0f, Color::orange);
    FillCircle(p[1], 5.0f, Color::red.Alpha(0.5f));
    FillCircle(p[2], 5.0f, Color::blue.Alpha(0.8f));
}

