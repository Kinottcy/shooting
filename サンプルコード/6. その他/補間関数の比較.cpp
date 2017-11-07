#include "Game.hpp"

float t;
int step;

void Start()
{
    step = 0;
    t = 0.0f;
}

typedef float (*InterpolationFunc)(float a, float b, float t);

struct InterpolationData {
    string name;
    InterpolationFunc func;
    Color color;
};

void DrawBall(const string& name, const Vector2& a, const Vector2& b, float t, InterpolationFunc p, const Color& color)
{
    float t2 = p(0.0f, 1.0f, t);
    
    DrawText(name, Vector2(-300, -10), Color::white);
    Vector2 pos = Vector2::Lerp(a, b, t2);
    FillCircle(pos, 10.0f, color);
    DrawText(FormatString("%.2f", t2), Vector2(260, -10), Color::white);
}

void DrawSquare(const string& name, const Color& a, const Color& b, float t, InterpolationFunc p)
{
    float t2 = p(0.0f, 1.0f, t);
    
    Color color = Color::Lerp(a, b, t2);
    FillRect(Rect(0, 0, 100, 100), color);
    DrawText(name, Vector2(0, -30), Color::white);
    
    DrawText(FormatString("%.2f", t2), Vector2(31, -2+30), Color::black);
    DrawText(FormatString("%.2f", t2), Vector2(30, 30), Color::white);
}


void Update()
{
    if (step == 0) {
        if (Input::GetKeyDown(KeyMask::Space)) {
            step = 1;
        }
    } else if (step == 1) {
        t += Time::deltaTime * 0.5f;
        if (t >= 1.0f) {
            t = 1.0f;
        }
        if (Input::GetKeyDown(KeyMask::Space)) {
            if (t < 1.0f) {
                step = 2;
            } else {
                t = 0.0f;
                step = 0;
            }
        }
        if (Input::GetKeyDown(KeyMask::Return)) {
            t = 0.0f;
            step = 0;
        }
    } else if (step == 2) {
        if (Input::GetKeyDown(KeyMask::Space)) {
            step = 1;
        }
        if (Input::GetKeyDown(KeyMask::Return)) {
            t = 0.0f;
            step = 0;
        }
    }
    
    Clear(Color::black);
    
    Vector2 a(-150, 0);
    Vector2 b(250, 0);
    Color c1 = Color::white;
    Color c2 = Color::blue;
    
    DrawLine({a.x, -50}, {a.x, 160}, Color::gray);
    DrawLine({b.x, -50}, {b.x, 160}, Color::gray);
    
    InterpolationData data[] = {
        { "Lerp", Mathf::Lerp, Color::orange },
        { "Ease-In", Mathf::EaseIn, Color::yellow },
        { "Ease-InOut", Mathf::EaseInOut, Color::green },
        { "Ease-Out", Mathf::EaseOut, Color::blue },
        { "SmoothStep", Mathf::SmoothStep, Color::purple },
    };
    
    for (int i = 0; i < sizeof(data) / sizeof(InterpolationData); i++) {
        SetModelTranslation(0, 110 - 30 * i);
        DrawBall(data[i].name, a, b, Mathf::Clamp01(t), data[i].func, data[i].color);
        
        SetModelTranslation(i * 120-300, -180);
        DrawSquare(data[i].name, c1, c2, t, data[i].func);
    }
    
    ResetModelTRS();
    DrawText("space:start/pause/reset, return:reset", {-50, 215}, Color::white);
    
    DrawText(FormatString("t = %.2f", t), {-300, 215}, Color::white);
}

