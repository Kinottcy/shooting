#include "Game.hpp"

Vector2 p[5];
Vector2 offset;
int dragIndex;

void Start()
{
    for (int i = 0; i < 5; i++) {
        p[i].x = (i - 2) * 50;
    }

    dragIndex = -1;
}

void Update()
{
    // ドラッグ処理のメイン部分
    if (dragIndex < 0) {
        if (Input::GetMouseButton(0)) {
            for (int i = 4; i >= 0; i--) {
                if (Vector2::Distance(p[i], GetMousePosition()) <= 20.0f) {
                    dragIndex = i;
                    offset = p[i] - GetMousePosition();
                    break;
                }
            }
        }
    } else {
        if (Input::GetMouseButton(0)) {
            p[dragIndex] = GetMousePosition() + offset;
        } else {
            dragIndex = -1;
        }
    }

    // 画面の描画
    Clear(Color::gray);

    Debug("[Drag System (Multiple)]");

    for (int i = 0; i < 5; i++) {
        FillCircle(p[i], 20.0f, Color::lightcyan);
        DrawCircle(p[i], 20.0f, 3.0f, Color::darkcyan);
    }
}

