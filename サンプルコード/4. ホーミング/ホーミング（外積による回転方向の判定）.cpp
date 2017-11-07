#include "Game.hpp"

Vector2 pos;
Vector2 target;
float angle;
float speed;

void Start()
{
    pos = {80, -50};
    target = {-150, -120};
    angle = 0.0f;
    speed = 100.0f;
}

void Update()
{
    if (Input::GetKey(KeyMask::LeftArrow)) {
        angle += M_PI * Time::deltaTime;
    }
    if (Input::GetKey(KeyMask::RightArrow)) {
        angle -= M_PI * Time::deltaTime;
    }

    // 外積の計算
    Vector2 dir(cosf(angle), sinf(angle));
    float cross = Vector2::Cross(dir, target - pos);

    // 回転と移動
    if (Input::GetKeyDown(KeyMask::Alpha1 | KeyMask::Keypad1)) {
        if (cross <= 0) {
            angle -= M_PI / 10;
        } else {
            angle += M_PI / 10;
        }
    }
    if (Input::GetKeyDown(KeyMask::Alpha2 | KeyMask::Keypad2)) {
        pos += Vector2(cosf(angle) * speed / 10, sinf(angle) * speed / 10);
    }

    // 画面のクリア
    Clear(Color::darkgray);

    // 操作説明の表示
    Debug("[Direction to Rotate]");
    Debug("<left><right> Change Direction");
    Debug("<1> Rotate   <2> Move");
    Debug();
    Debug("Angle: %.2f prad", angle / M_PI);
    Debug("Cross: %.2f", cross);

    // 移動範囲の描画
    FillCircle(pos, speed, Color::lightcyan);

    // 現在位置と方向の描画
    Vector2 head = pos + Vector2(cosf(angle) * 20.0f, sinf(angle) * 20.0f);
    DrawLine(pos, head, 2.0f, Color::black);
    FillCircle(pos, 10.0f, Color::blue);

    // ターゲットの描画
    FillCircle(target, 10.0f, Color::pink);
}

