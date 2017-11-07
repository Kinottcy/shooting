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

    // 回転候補の作成
    Vector2 next[3];
    next[0] = pos + Vector2(cosf(angle-M_PI/5) * speed, sinf(angle-M_PI/5) * speed);
    next[1] = pos + Vector2(cosf(angle) * speed, sinf(angle) * speed);
    next[2] = pos + Vector2(cosf(angle+M_PI/5) * speed, sinf(angle+M_PI/5) * speed);

    // 最短の回転先の選択
    float d[3];
    for (int i = 0; i < 3; i++) {
        d[i] = (target - next[i]).SqrMagnitude();
    }
    float dist = d[0];
    int minIndex = 0;
    if (d[1] < dist) {
        dist = d[1];
        minIndex = 1;
    }
    if (d[2] < dist) {
        minIndex = 2;
    }

    // 回転と移動
    if (Input::GetKeyDown(KeyMask::Alpha1 | KeyMask::Keypad1)) {
        if (minIndex == 0) {
            angle -= M_PI / 10;
        } else if (minIndex == 2) {
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
    for (int i = 0; i < 3; i++) {
        Debug("d%d: %.2f", i, d[i]);
    }

    // 移動範囲の描画
    FillCircle(pos, speed, Color::lightcyan);

    // 最短距離の描画
    DrawLine(target, next[minIndex], 2.0f, Color::white);

    // 移動先候補の描画
    for (int i = 0; i < 3; i++) {
        DrawLine(pos, next[i], 1.0f, Color::black.Alpha(0.3f));
        if (i == minIndex) {
            FillCircle(next[i], 10.0f, Color::orange.Alpha(0.85f));
        } else {
            FillCircle(next[i], 10.0f, Color::lightorange.Alpha(0.4f));
        }
    }

    // 現在位置と方向の描画
    Vector2 head = pos + Vector2(cosf(angle) * 20.0f, sinf(angle) * 20.0f);
    DrawLine(pos, head, 2.0f, Color::black);
    FillCircle(pos, 10.0f, Color::blue);

    // ターゲットの描画
    FillCircle(target, 10.0f, Color::pink);
}

