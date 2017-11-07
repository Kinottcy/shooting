#include "Game.hpp"

Vector2 p;
Vector2 offset;
bool isDragging;

void Start()
{
    isDragging = false;
}

void Update()
{
    if (!isDragging) {
        if (Input::GetMouseButton(0)) {
            if (Vector2::Distance(p, GetMousePosition()) <= 50.0f) {
                offset = p - GetMousePosition();
                isDragging = true;
            }
        }
    } else {
        if (Input::GetMouseButton(0)) {
            p = GetMousePosition() + offset;
        } else {
            isDragging = false;
        }
    }

    Clear(Color::gray);

    Debug("[Drag System]");
    Debug("Center: (%d, %d)", (int)p.x, (int)p.y);

    FillCircle(p, 50.0f, Color::lightcyan);
    DrawCircle(p, 50.0f, 3.0f, Color::darkcyan);
}

