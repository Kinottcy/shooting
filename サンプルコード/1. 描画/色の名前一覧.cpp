#include "Game.hpp"

void Start()
{
    // Do nothing
}

void DrawColorBox(int x, int y, Color color, string name)
{
    static const Vector2 kBoxSize(60, 23);

    Rect rect(120 + x * (kBoxSize.x + 110), Screen::height - (kBoxSize.y + 20) * (y + 1) - 12, kBoxSize.x, kBoxSize.y);
    FillRect(rect, color);
    DrawRect(rect, Color::white);

    DrawTextCenter(name, Vector2(rect.Center().x, rect.y-15), Color::white);
}

void Update()
{
    Clear(Color::black);

    SetCameraTranslation(Screen::size() / 2);

    SetFont("nicoca_v1.ttf", 20.0f);
    DrawTextRight("色の名前一覧", Vector2(Screen::width - 40, Screen::height - 40), Color::white);

    SetFont("nicoca_v1.ttf", 13.0f);
    DrawColorBox(0, 0, Color::white, "Color::white");
    DrawColorBox(1, 0, Color::black, "Color::black");

    DrawColorBox(0, 1, Color::darkblue, "Color::darkblue");
    DrawColorBox(0, 2, Color::darkcyan, "Color::darkcyan");
    DrawColorBox(0, 3, Color::darkgray, "Color::darkgray");
    DrawColorBox(0, 4, Color::darkgreen, "Color::darkgreen");
    DrawColorBox(0, 5, Color::darkorange, "Color::darkorange");
    DrawColorBox(0, 6, Color::darkpink, "Color::darkpink");
    DrawColorBox(0, 7, Color::darkpurple, "Color::darkpurple");
    DrawColorBox(0, 8, Color::darkred, "Color::darkred");
    DrawColorBox(0, 9, Color::darkyellow, "Color::darkyellow");

    DrawColorBox(1, 1, Color::blue, "Color::blue");
    DrawColorBox(1, 2, Color::cyan, "Color::cyan");
    DrawColorBox(1, 3, Color::gray, "Color::gray");
    DrawColorBox(1, 4, Color::green, "Color::green");
    DrawColorBox(1, 5, Color::orange, "Color::orange");
    DrawColorBox(1, 6, Color::pink, "Color::pink");
    DrawColorBox(1, 7, Color::purple, "Color::purple");
    DrawColorBox(1, 8, Color::red, "Color::red");
    DrawColorBox(1, 9, Color::yellow, "Color::yellow");

    DrawColorBox(2, 1, Color::lightblue, "Color::lightblue");
    DrawColorBox(2, 2, Color::lightcyan, "Color::lightcyan");
    DrawColorBox(2, 3, Color::lightgray, "Color::lightgray");
    DrawColorBox(2, 4, Color::lightgreen, "Color::lightgreen");
    DrawColorBox(2, 5, Color::lightorange, "Color::lightorange");
    DrawColorBox(2, 6, Color::lightpink, "Color::lightpink");
    DrawColorBox(2, 7, Color::lightpurple, "Color::lightpurple");
    DrawColorBox(2, 8, Color::lightred, "Color::lightred");
    DrawColorBox(2, 9, Color::lightyellow, "Color::lightyellow");
}

