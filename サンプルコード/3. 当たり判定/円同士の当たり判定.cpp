#include "Game.hpp"

Vector2 p[4];
float dx;
int dragTarget;

void Start()
{
    p[0] = { -100, 0 }; // 円1の中心点
    p[1] = { 10, 0 };   // 円1の右端の点
    p[2] = { 50, 0 };   // 円2の中心点
    p[3] = { 100, 0 };  // 円2の右端の点

    dragTarget = -1;
}

/// 円同士の当たり判定
bool CheckHit(const Vector2& c1, float r1, const Vector2& c2, float r2)
{
    return ((c2 - c1).Magnitude() <= r1 + r2);
    //return (c2 - c1).SqrMagnitude() <= (r1 + r2) * (r1 + r2);
}

void Update()
{
    // 操作点のドラッグ
    if (dragTarget < 0) {
        if (Input::GetMouseButton(0)) {
            for (int i = 0; i < 4; i++) {
                if (Vector2::Distance(p[i], GetMousePosition()) <= 10.0f) {
                    dragTarget = i;
                    if (dragTarget == 0 || dragTarget == 2) {
                        dx = p[dragTarget+1].x - p[dragTarget].x;
                    }
                    break;
                }
            }
        }
    } else {
        if (Input::GetMouseButton(0)) {
            p[dragTarget] = GetMousePosition();
            if (dragTarget == 0 || dragTarget == 2) {
                p[dragTarget+1].x = p[dragTarget].x + dx;
                p[dragTarget+1].y = p[dragTarget].y;
            } else if (dragTarget == 1 || dragTarget == 3) {
                p[dragTarget].y = p[dragTarget-1].y;
            }
        } else {
            dragTarget = -1;
        }
    }

    // 画面の描画
    Clear(Color::gray);

    Debug("[HitTest between Circles]");

    float r[] = {
        Vector2::Distance(p[0], p[1]),
        Vector2::Distance(p[2], p[3])
    };

    bool hit = CheckHit(p[0], r[0], p[2], r[1]);
    for (int i = 0; i < 2; i++) {
        if (hit) {
            FillCircle(p[i*2], r[i], Color::lightcyan.Alpha(0.8f));
        } else {
            FillCircle(p[i*2], r[i], Color::lightpink);
        }
        DrawCircle(p[i*2], r[i], 3.0f, Color::darkcyan);
        DrawLine(p[i*2], p[i*2+1], 1.0f, Color::black.Alpha(0.3f));
    }

    FillCircle(p[0], 5.0f, Color::orange);
    FillCircle(p[2], 5.0f, Color::orange);
    FillCircle(p[1], 5.0f, Color::red.Alpha(0.5f));
    FillCircle(p[3], 5.0f, Color::red.Alpha(0.5f));
}

