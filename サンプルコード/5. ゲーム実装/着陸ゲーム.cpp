#include "Game.hpp"

struct Star
{
    int x, y;
    Color color;
    Color colors[5] = { Color::purple, Color::green, Color::cyan, Color::yellow, Color::white };

    Star() {
        x = Random::IntValue(640);
        y = Random::IntValue(480);
        color = colors[Random::IntValue(5)];
    }

    void Draw() {
        DrawPoint(Vector2(x, y), color);
    }
};

struct Line
{
    Vector2 p[2];

    Line(const Vector2& p0, const Vector2& p1)
    {
        p[0] = p0;
        p[1] = p1;
    }

    void Draw()
    {
        FillTriangle(Vector2(p[0].x, 0), p[0], p[1], Color::darkred);
        FillTriangle(Vector2(p[0].x, 0), p[1], Vector2(p[1].x, 0), Color::darkred);
        DrawLine(p[0], p[1], 1.0f, Color::red);
    }

    bool HitTest(const Vector2& pos)
    {
        if (pos.x < p[0].x || pos.x > p[1].x) {
            return false;
        }
        Vector2 a(p[1] - p[0]);
        Vector2 b(pos - p[0]);
        return (Vector2::Cross(a, b) <= 0.0f);
    }
};

vector<Star*> stars;
vector<Line*> lines;
Rect baseRect(0, 0, 25, 5);
Vector2 playerPos;
int state;
float startTime;
float gravity;
float speed;
float fuel;
float windSpeed;

void MakeStars()
{
    for (auto star : stars) {
        delete star;
    }
    stars.clear();

    for (int i = 0; i < 500; i++) {
        stars.push_back(new Star());
    }
}

void MakeStage()
{
    for (auto line : lines) {
        delete line;
    }
    lines.clear();

    baseRect.x = -1;
    Vector2 pos(0, 180);
    Vector2 oldPos = pos;
    int baseX = Random::IntValue(590);
    while (pos.x < 639) {
        pos.x += Random::IntRange(1, 30);
        pos.y += Random::IntRange(-75, 75);
        pos.y = Mathf::Clamp(pos.y, 130, 330);
        if (pos.x > baseX && baseRect.x < 0) {
            if (pos.y >= 205) {
                pos.y -= 125;
            }
            baseRect.x = pos.x;
            baseRect.y = pos.y - 4;
            lines.push_back(new Line(oldPos, pos));
            oldPos = pos;
            pos.x += 25;
        }
        lines.push_back(new Line(oldPos, pos));
        oldPos = pos;
    }
}

void DrawPlayer(bool hasFire)
{
    FillCircle({0, 0}, {8, 6}, Color::gray);
    FillCircle({0, 2}, {4, 3}, Color::lightgray);
    DrawCircle({0, 0}, {8, 6}, 1.0f, Color::white);
    FillRect(Rect{-6, -9, 12, 5}, Color::gray);
    DrawRect(Rect{-6, -9, 12, 5}, 1.0f, Color::white);
    FillRect(Rect{-8, -14, 2, 5}, Color::lightgray);
    FillRect(Rect{6, -14, 2, 5}, Color::lightgray);
    if (hasFire) {
        FillCircle({0, -14}, {4.0f, 6.0f}, Color::red.Alpha(0.5f));
        FillCircle({0, -12}, 1.5f, Color::yellow);
    }
}

void InitGame()
{
    MakeStars();
    MakeStage();

    playerPos = {320, 440};
    gravity = Random::FloatRange(0.8f, 5.0f);
    speed = 1.0f;
    fuel = 1200.0f;
    windSpeed = Random::FloatRange(-10.0f, 10.0f);

    state = 0;
    startTime = 1.8f;
}

void Start()
{
    InitGame();
}

void DrawInfoTexts()
{
    SetFont("nicoca_v1.ttf", 20.0f);

    Vector2 upperLeft(-Screen::width/2 + 4, Screen::height/2-20);
    DrawText(FormatString("Gravity:%3.1f", gravity), upperLeft, Color::white);
    DrawText(FormatString("Wind:%+3.1f", windSpeed), upperLeft-Vector2(0, 20), Color::white);
    DrawText(FormatString("Speed:%5.1f", speed), upperLeft+Vector2(230, 0), Color::white);
    DrawText(FormatString("Fuel:%6.1f", fuel), upperLeft+Vector2(450, 0), Color::white);
}

void Update()
{
    // 背景のクリア
    Clear(Color::black);

    // 重力や速度などの情報テキストを描画
    SetLayer(10);
    DrawInfoTexts();

    // メインの描画
    SetLayer(0);
    SetCameraTranslation(320, 240);

    for (auto star : stars) {
        star->Draw();
    }
    for (auto line : lines) {
        line->Draw();
    }
    FillRect(baseRect, Color::cyan);

    SetModelTranslation(playerPos);
    DrawPlayer(state == 1 && Input::GetKey(KeyMask::UpArrow));

    // ゲーム開始時の処理
    if (state == 0) {
        SetModelTranslation(320, 260);
        if ((int)(Time::time*4) % 2 == 0) {
            SetFont("nicoca_v1.ttf", 40.0f);
            DrawTextCenter("START", {0, 0}, Color::green);
        }
        startTime -= Time::deltaTime;
        if (startTime <= 0.0f) {
            state = 1;
        }
    }
    // プレイ時の処理
    else if (state == 1) {
        if (Input::GetKey(KeyMask::LeftArrow)) {
            playerPos.x -= 50.0f * Time::deltaTime;
        }
        if (Input::GetKey(KeyMask::RightArrow)) {
            playerPos.x += 50.0f * Time::deltaTime;
        }
        if (Input::GetKey(KeyMask::UpArrow)) {
            speed -= gravity / 2.0f;
            fuel -= gravity / 2.0f;
        }
        speed += gravity / 10.0f;
        fuel -= 1.0f;
        playerPos.x += windSpeed * Time::deltaTime;
        playerPos.y -= speed * Time::deltaTime;
        if (playerPos.x < 0.0f) {
            playerPos.x = 0.0f;
        }
        if (playerPos.x > 640.0f) {
            playerPos.x = 640.0f;
        }
        if (playerPos.y > 480.0f) {
            playerPos.y = 480.0f;
        }
        Vector2 check1 = playerPos + Vector2(-8, -12);
        Vector2 check2 = playerPos + Vector2(8, -12);
        Vector2 check3 = playerPos + Vector2(0, -12);
        if (baseRect.Contains(check1) && baseRect.Contains(check2)) {
            if (speed > 30.0f) {
                state = 5;
            } else {
                state = 2;
            }
        } else {
            bool hit = false;
            for (auto line : lines) {
                if (line->HitTest(check1) || line->HitTest(check2) || line->HitTest(check3)) {
                    hit = true;
                    break;
                }
            }
            if (hit) {
                state = 3;
            } else if (fuel < 0.0f) {
                state = 4;
            }
        }
    }
    // ゲームクリア時の処理
    else if (state == 2) {
        SetModelTranslation(320, 260);
        SetFont("nicoca_v1.ttf", 40.0f);
        DrawTextCenter("NICE!", {0, 0}, Color::cyan);
        SetModelTranslation(320, 240);
        SetFont("nicoca_v1.ttf", 20.0f);
        DrawTextCenter("PUSH RET KEY", {0, 0}, Color::cyan);
        if (Input::GetKeyDown(KeyMask::Return)) {
            InitGame();
        }
    }
    // ゲームオーバー時の処理
    else if (state == 3 || state == 4 || state == 5) {
        FillCircle({10, 10}, 20.0f, Color::yellow.Alpha(0.8f));
        FillCircle({-20, -10}, 20.0f, Color::yellow.Alpha(0.6f));
        FillCircle({0, -20}, 20.0f, Color::yellow.Alpha(0.5f));
        SetModelTranslation(320, 260);
        SetFont("nicoca_v1.ttf", 40.0f);
        if (state == 3) {
            DrawTextCenter("CRASH!", {0, 0}, Color::purple);
        } else if (state == 4) {
            DrawTextCenter("NO FUEL!", {0, 0}, Color::purple);
        } else {
            DrawTextCenter("TOO FAST!", {0, 0}, Color::purple);
        }
        SetModelTranslation(320, 240);
        SetFont("nicoca_v1.ttf", 20.0f);
        DrawTextCenter("PUSH RET KEY", {0, 0}, Color::purple);
        if (Input::GetKeyDown(KeyMask::Return)) {
            InitGame();
        }
    }
}

