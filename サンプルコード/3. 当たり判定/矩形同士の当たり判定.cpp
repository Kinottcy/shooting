#include "Game.hpp"

Vector2 p[4];
int dragTarget;

void Start()
{
    p[0] = { -150, -100 };  // 矩形1の左下の頂点
    p[1] = { 50, 50 };      // 矩形1の右上の頂点
    p[2] = { 0, 0 };        // 矩形2の左下の頂点
    p[3] = { 100, 100 };    // 矩形2の右上の頂点

    dragTarget = -1;
}

bool HitTest(const Rect& rect1, Rect& rect2)
{
    //return rect1.Overlaps(rect2);

    float minX1 = rect1.xMin();
    float minY1 = rect1.yMin();
    float maxX1 = rect1.xMax();
    float maxY1 = rect1.yMax();

    float minX2 = rect2.xMin();
    float minY2 = rect2.yMin();
    float maxX2 = rect2.xMax();
    float maxY2 = rect2.yMax();

    return (minX1 < maxX2 && maxX1 > minX2 &&
            minY1 < maxY2 && maxY1 > minY2);
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

    Debug("[HitTest between Rects]");

    Rect rect[2];
    for (int i = 0; i < 2; i++) {
        float minX = std::min(p[i*2].x, p[i*2+1].x);
        float minY = std::min(p[i*2].y, p[i*2+1].y);
        float maxX = std::max(p[i*2].x, p[i*2+1].x);
        float maxY = std::max(p[i*2].y, p[i*2+1].y);
        rect[i] = Rect(minX, minY, maxX - minX, maxY - minY);
    }

    bool hit = HitTest(rect[0], rect[1]);
    for (int i = 0; i < 2; i++) {
        if (hit) {
            FillRect(rect[i], Color::lightcyan.Alpha(0.75f));
        } else {
            FillRect(rect[i], Color::lightpink);
        }
        DrawRect(rect[i], 3.0f, Color::darkcyan);
    }

    for (int i = 0; i < 4; i++) {
        FillCircle(p[i], 5.0f, Color::orange);
    }
}

