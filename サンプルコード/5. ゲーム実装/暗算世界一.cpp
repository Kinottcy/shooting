#include "Game.hpp"

Color colors[15];

struct Box {
    Rect rect;
    Color color;

    Box()
    {
        Vector2 p1(Random::IntRange(0, 639), Random::IntRange(0, 479));
        Vector2 p2(Random::IntRange(0, 639), Random::IntRange(0, 479));
        Vector2 min = Vector2::Min(p1, p2);
        Vector2 max = Vector2::Max(p1, p2);
        rect = Rect(min, max-min);
        color = colors[Random::IntRange(1, 14)];
    }

    void Draw()
    {
        DrawRect(rect, color);
    }
};

struct Star {
    Vector2 pos;
    Color color;

    Star()
    {
        pos = Vector2(Random::IntRange(0, 639), Random::IntRange(0, 479) - 480);
        color = colors[Random::IntRange(1, 14)];
    }

    void Draw()
    {
        DrawPoint(pos, color);
    }
};

vector<Box> boxes;
vector<Star> stars;
int step;
float scrollTime;
string enemyNames[] = { "スライム", "ガーゴイル", "魔道士", "ドラゴン", "ニュートン" };
string startMessages[] = { "この問題が解けるかな？", "よーし頑張れ！", "難しすぎて解けまい…", "難易度Ｃ級！！", "気合いで解こうぜ！！" };

int age;
int attack;
int defence;
int hp;
int correctCount;
int wrongCount;
int level;
int currentHP;
int enemyIndex;
int enemyAttack;
int enemyDefence;
int enemyHP;

int playStep;
vector<string> textLines;
bool keyWait;
string valueStr;
float inputTime;
int answer;
float bonus;
int damage;


void InitGame()
{
    age = 20;
    attack = 50;
    defence = 10;
    hp = 200;
    correctCount = 0;
    wrongCount = 0;
    level = 1;
    keyWait = false;

    playStep = 0;

    enemyIndex = Random::IntRange(0, 4);
    enemyAttack = Random::IntRange(10, 110) + defence;
    enemyDefence = Random::IntRange(0, attack);
    enemyHP = Random::IntRange(0, hp) + 30;

    textLines.clear();
}

void Start()
{
    static Color c[] = {
        Color::black, Color::blue, Color::red, Color::purple, Color::green,
        Color::cyan, Color::yellow, Color::white,
        Color::darkblue, Color::darkred, Color::darkpurple, Color::darkgreen,
        Color::darkcyan, Color::darkyellow, Color::gray,
    };
    for (int i = 0; i < 14; i++) {
        colors[i] = c[i];
    }

    for (int i = 0; i < 120; i++) {
        boxes.push_back(Box());
    }
    for (int i = 0; i < 350; i++) {
        stars.push_back(Star());
    }
    scrollTime = 0.0f;
    step = 0;
}

void DrawBackground()
{
    // タイトル画面の描画
    for (auto& box : boxes) { box.Draw(); }
    FillCircle({320, 240}, {200, 200.0f/3}, Color::white.Alpha(0.8f));
    SetFont("nicoca_v1.ttf", 40.0f);
    DrawTextCenter("暗算世界一", {320, 240+15-10-4}, Color::darkgray);
    DrawTextCenter("暗算世界一", {320, 240+15-10}, Color::white);
    SetFont("nicoca_v1.ttf", 32.0f);
    DrawTextCenter("PUSH KEY", {320, 240-30-10-4}, Color::darkgray);
    DrawTextCenter("PUSH KEY", {320, 240-30-10}, Color::white);

    // 出題画面の描画
    for (auto& star : stars) { star.Draw(); }
    for (int i = 0; i <= 6; i+=2) {
        FillRect(Rect(124+i, (20+i)-480+250, 504-124-i*2, 154-20+30-i*2), colors[i+1]);
        FillRect(Rect(124+i, (290+i)-480-250, 504-124-i*2, 380-290-i*2), colors[7-i]);
    }
}

void AddTextLine(const string& text)
{
    textLines.push_back(text);
    if (textLines.size() >= 5) {
        textLines.erase(textLines.begin());
    }
}

void DrawStatusText(const string& title, const string& status, const Vector2& center, float padding, const Color& color)
{
    DrawTextRight(title, center - Vector2(padding/2, 0), color);
    DrawText(status, center + Vector2(padding/2, 0), color);
}

void DrawStatus()
{
    SetFont("nicoca_v1.ttf", 18.0f);

    int ratio = (correctCount == 0)? 0: (int)((float)correctCount / (correctCount + wrongCount) * 100);

    int startY = -85;
    int rightX = 200;
    int lineHeight = -20;
    int padding = 12;

    int y = 0;
    DrawStatusText("名　前", "あなた",
                   Vector2(rightX, y*lineHeight+startY), padding, Color::black);
    y++;
    DrawStatusText("ＬＶ", FormatString("%d", level),
                   Vector2(rightX, y*lineHeight+startY), padding, Color::black);
    y++;
    DrawStatusText("生命力", FormatString("%d", currentHP),
                   Vector2(rightX, y*lineHeight+startY), padding, Color::black);
    y++;
    DrawStatusText("攻撃力", FormatString("%d", attack),
                   Vector2(rightX, y*lineHeight+startY), padding, Color::black);
    y++;
    DrawStatusText("守備力", FormatString("%d", defence),
                   Vector2(rightX, y*lineHeight+startY), padding, Color::black);
    y++;
    DrawStatusText("正解率", FormatString("%d%%", ratio),
                   Vector2(rightX, y*lineHeight+startY), padding, Color::black);

    rightX = 400;
    y = 0;
    DrawStatusText("名　前", enemyNames[enemyIndex],
                   Vector2(rightX, y*lineHeight+startY), padding, Color::black);
    y = 2;
    DrawStatusText("生命力", FormatString("%d", enemyHP),
                   Vector2(rightX, y*lineHeight+startY), padding, Color::black);
    y++;
    DrawStatusText("攻撃力", FormatString("%d", enemyAttack),
                   Vector2(rightX, y*lineHeight+startY), padding, Color::black);
    y++;
    DrawStatusText("守備力", FormatString("%d", enemyDefence),
                   Vector2(rightX, y*lineHeight+startY), padding, Color::black);
}

void Update()
{
    if (step == 0) {
        if (Input::GetKeyDown(KeyMask::Any)) {
            step = 1;
        }
    } else if (step == 1) {
        scrollTime += Time::deltaTime;
        if (scrollTime >= 1.0f) {
            scrollTime = 1.0f;
            InitGame();
            step = 2;
        }
    } else if (step == 2) {
        if (keyWait) {
            if (playStep == 2) {
                inputTime -= Time::deltaTime;
                if (Input::GetKeyDown(KeyMask::Alpha0 | KeyMask::Keypad0)) {
                    valueStr += "0";
                } else if (Input::GetKeyDown(KeyMask::Alpha1 | KeyMask::Keypad1)) {
                    valueStr += "1";
                } else if (Input::GetKeyDown(KeyMask::Alpha2 | KeyMask::Keypad2)) {
                    valueStr += "2";
                } else if (Input::GetKeyDown(KeyMask::Alpha3 | KeyMask::Keypad3)) {
                    valueStr += "3";
                } else if (Input::GetKeyDown(KeyMask::Alpha4 | KeyMask::Keypad4)) {
                    valueStr += "4";
                } else if (Input::GetKeyDown(KeyMask::Alpha5 | KeyMask::Keypad5)) {
                    valueStr += "5";
                } else if (Input::GetKeyDown(KeyMask::Alpha6 | KeyMask::Keypad6)) {
                    valueStr += "6";
                } else if (Input::GetKeyDown(KeyMask::Alpha7 | KeyMask::Keypad7)) {
                    valueStr += "7";
                } else if (Input::GetKeyDown(KeyMask::Alpha8 | KeyMask::Keypad8)) {
                    valueStr += "8";
                } else if (Input::GetKeyDown(KeyMask::Alpha9 | KeyMask::Keypad9)) {
                    valueStr += "9";
                } else if (Input::GetKeyDown(KeyMask::Backspace)) {
                    if (valueStr.length() > 0) {
                        valueStr = valueStr.substr(0, valueStr.length()-1);
                    }
                }
                if (Input::GetKeyDown(KeyMask::Return)) {
                    string str = *(textLines.end() - 1);
                    textLines.erase(textLines.end() - 1);
                    AddTextLine(str + valueStr);
                    keyWait = false;
                    playStep++;
                } else if (inputTime <= 0.0f) {
                    string str = *(textLines.end() - 1);
                    textLines.erase(textLines.end() - 1);
                    AddTextLine(str + valueStr);
                    if (valueStr.length() == 0) {
                        AddTextLine("時間切れ！！！！");
                    }
                    keyWait = false;
                    playStep++;
                }
            } else {
                if (Input::GetKeyDown(KeyMask::Any)) {
                    keyWait = false;
                    playStep++;
                }
            }
        } else {
            if (playStep == 0) {
                AddTextLine("戦闘を開始します。");
                currentHP = hp;
                keyWait = true;
            } else if (playStep == 1) {
                AddTextLine(FormatString("%sの攻撃だ！！", enemyNames[enemyIndex].c_str()));
                keyWait = true;
            } else if (playStep == 2) {
                AddTextLine(startMessages[Random::IntRange(0, 4)]);
                int p = Random::IntRange(0, age * 10);
                int q = Random::IntRange(0, age * 10);
                if (Random::IntRange(0, 1) == 0) {
                    answer = p + q;
                    bonus = 1.0f;
                    AddTextLine(FormatString("　%d + %d = ", p, q));
                } else {
                    if (p < q) {
                        swap(p, q);
                    }
                    answer = p - q;
                    bonus = 1.5f;
                    AddTextLine(FormatString("　%d - %d = ", p, q));
                }
                inputTime = 5.0f;
                keyWait = true;
            } else if (playStep == 3) {
                int value = atoi(valueStr.c_str());
                valueStr = "";
                if (value == answer) {
                    AddTextLine("正解っ！敵の攻撃を跳ね返した！！");
                    correctCount++;
                    playStep = 10;
                } else {
                    AddTextLine(FormatString("不正解っ！正解は %d だっ！", answer));
                    wrongCount++;
                    playStep = 20;
                }
                keyWait = true;
            } else if (playStep == 11) {
                damage = (int)((attack - enemyDefence) * Random::FloatRange(1, 2) * bonus);
                if (damage < 1) {
                    damage = 1;
                }
                AddTextLine(FormatString("%sに %d のダメージを与えた！！", enemyNames[enemyIndex].c_str(), damage));
                keyWait = true;
            } else if (playStep == 12) {
                enemyHP -= damage;
                if (enemyHP <= 0) {
                    AddTextLine("あなたの勝利です！！");
                    keyWait = true;
                } else {
                    playStep = 1;
                }
            } else if (playStep == 13) {
                step = 3;
            } else if (playStep == 15) {
                level++;
                hp += level * 3;
                attack += level;
                defence += level;
                playStep = 1;
            } else if (playStep == 21) {
                damage = (int)((enemyAttack - defence) * Random::FloatRange(1, 2) * bonus);
                if (damage < 1) {
                    damage = 1;
                }
                AddTextLine(FormatString("あなたは %d のダメージを受けた！！", damage));
                keyWait = true;
            } else if (playStep == 22) {
                currentHP -= damage;
                if (currentHP <= 0) {
                    AddTextLine("あなたは敗れた…");
                    playStep = 90;
                    keyWait = true;
                } else {
                    playStep = 1;
                }
            } else if (playStep == 91) {
                step = 3;
            }
        }
    } else if (step == 3) {
        scrollTime -= Time::deltaTime;
        if (scrollTime <= 0.0f) {
            scrollTime = 0.0f;
            step = 0;
        }
    }

    Clear(Color::black);

    Vector2 scrollA(Screen::size()/2);
    Vector2 scrollB(Screen::size()/2 - Vector2(0, Screen::size().y));
    SetCameraTranslation(Vector2::SmoothStep(scrollA, scrollB, scrollTime));

    DrawBackground();
    if (step == 2) {
        SetFont("nicoca_v1.ttf", 18.0f);
        int i = 0;
        for (; i < textLines.size(); i++) {
            DrawText(textLines[i], Vector2(160, -380-i*16), Color::white);
        }
        if (keyWait) {
            Vector2 size = GetTextSize(textLines[i-1]);
            if (playStep == 2) {
                DrawText(valueStr, Vector2(160 + size.x, -380-(i-1)*16), Color::white);
                size.x += GetTextSize(valueStr).x;
            }
            if ((int)(Time::time * 2) % 2 == 0) {
                FillRect(Rect(160 + size.x, -380-(i-1)*16, 8, 16), Color::white);
            }
        }

        if (playStep >= 1) {
            DrawStatus();
        }
    }
}

