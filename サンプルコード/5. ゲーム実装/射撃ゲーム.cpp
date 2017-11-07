#include "Game.hpp"


const int kGameOverScore = 5;

Vector2 playerPos[2];
Vector2 targetPos;
int scores[2];
float angle;
float angleSpeed;
Vector2 bulletPos[2];
Vector2 bulletSpeed[2];
float hitTime;


void InitGame()
{
    playerPos[0] = { 25, 98 };
    playerPos[1] = { 614, 98 };
    angle = 0.0f;
    angleSpeed = 2.0f;
    bulletPos[0].y = -1;
    bulletPos[1].y = -1;
    hitTime = -1.0f;
    targetPos.x = Random::IntRange(120, 520);
    targetPos.y = 113;
}

void Start()
{
    scores[0] = 0;
    scores[1] = 0;
    InitGame();
}

void Update()
{
    // 背景のクリア
    Clear(Color::cyan);
    SetCameraTranslation(320, 240);

    // メインの描画
    FillRect(Rect(0, 0, 640, 98), Color::green);
    for (int i = 0; i < 2; i++) {
        FillCircle(playerPos[i], {15, 15}, 0.0f, M_PI, Color::red, Color::red);
        FillRect(Rect(playerPos[i].x-5, playerPos[i].y+12, 10, 3), Color::cyan);
    }
    FillCircle(targetPos, 15.0f, Color::white);
    DrawCircle(targetPos, 15.0f, 1.0f, Color::black);
    DrawCircle(targetPos, 10.0f, 1.0f, Color::black);
    DrawLine({0, 98}, {640, 98}, 1.0f, Color::black);

    // 砲台の移動
    if (hitTime < 0.0f) {
        angle += angleSpeed * Time::deltaTime;
        if (angle >= M_PI/2) {
            angle = M_PI/2;
            angleSpeed *= -1;
        }
        if (angle <= 0.0f) {
            angle = 0.0f;
            angleSpeed *= -1;
        }
    }
    // ヒット時の処理
    else {
        hitTime += Time::deltaTime;
        float hitSize = Mathf::Lerp(0.0f, 40.0f, hitTime);
        FillCircle(targetPos+Vector2(0, -15), Vector2(hitSize, hitSize), 0.0f, M_PI, Color::red.Alpha(0.8f), Color::red.Alpha(0.8f));
    }

    // 砲台の描画
    float co = cosf(angle);
    float si = sinf(angle);
    Vector2 cannonPos(si * 23, co * 23);
    for (int i = 0; i < 2; i++) {
        Vector2 cannonBase(playerPos[i].x, 116);
        if (i == 1) {
            cannonPos.x *= -1;
        }
        DrawLine(cannonBase, cannonBase + cannonPos, 1.0f, Color::red);
        if (hitTime < 0.0f && bulletPos[i].y < 0) {
            if ((i == 0 && Input::GetKeyDown(KeyMask::LeftShift | KeyMask::RightShift)) ||
                (i == 1 && Input::GetKeyDown(KeyMask::Return)))
            {
                bulletPos[i] = playerPos[i] + Vector2(0, 18);
                bulletSpeed[i] = cannonPos;
            }
        }
    }

    // 弾の移動
    for (int i = 0; i < 2; i++) {
        if (bulletPos[i].y > 0) {
            bulletPos[i] += bulletSpeed[i] * Time::deltaTime * 23;
            bulletSpeed[i].y += -21.0f * Time::deltaTime;
            if (bulletPos[i].y < 116-16) {
                bulletPos[i].y = -1;
            } else {
                if ((bulletPos[i] - targetPos).SqrMagnitude() < 24*24) {
                    scores[i] += 1;
                    bulletPos[0].y = -1;
                    bulletPos[1].y = -1;
                    hitTime = 0.0f;
                }
            }
        }
        if (bulletPos[i].y > 0) {
            FillCircle(bulletPos[i], 5.0f, Color::red);
        }
    }

    // スコアなどの表示
    ResetCameraTRS();
    ResetModelTRS();
    SetFont("nicoca_v1.ttf", 20.0f);
    for (int i = 0; i < 2; i++) {
        DrawText(FormatString("PLAYER%d   %d", i+1, scores[i]), Vector2(-Screen::width/2+30+i*350, Screen::height/2-40), Color::darkblue);
    }
    if (hitTime >= 1.0f) {
        if (scores[0] == kGameOverScore || scores[1] == kGameOverScore) {
            SetFont("nicoca_v1.ttf", 40.0f);
            DrawTextCenter("GAME OVER", {0, 20}, Color::red);
            SetFont("nicoca_v1.ttf", 20.0f);
            DrawTextCenter(FormatString("PLAYER%d WIN!!", (scores[0] == 2)? 1: 2), {0, -20}, Color::red);
            DrawTextCenter("PUSH SPACE KEY", {0, -60}, Color::red);
            if (Input::GetKeyDown(KeyMask::Space)) {
                scores[0] = 0;
                scores[1] = 0;
                hitTime = 0.0f;
                InitGame();
            }
        } else {
            hitTime = 0.0f;
            InitGame();
        }
    }
}

