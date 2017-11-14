#include "Game.hpp"
#include<math.h>

// TODO: 砲台の位置を画面左に、ターゲットの位置を画面右に移動させる。(A)
// TODO: 雲の位置を左から右に動かす。見えなくなったら左端に戻す。(B)
// TODO: 砲台を青い壁に沿って上下に動かす。(C)
// TODO: 弾のスピードを速くし、弾が画面右端を通り越したら再度発射可能にする。(D)
// TODO: スコアのサイズを大きくする。(E)
// TODO: スコアを100点ずつ加算するようにし、5桁の表示に変える。(F)
// TODO: PlayBGM()関数を使って、BGMを再生する。(G) HW16A063 木下直矢
// TODO: PlaySE()関数を使って、弾の発射時とターゲットに当たった時にSEを再生する。(H) HW16A063 木下直矢
// TODO: PlayBGM()関数を使って、BGMを再生する。(G)
// TODO: PlaySE()関数を使って、弾の発射時とターゲットに当たった時にSEを再生する。(H)

class class_score{
public:
    int bg1,bg2,flag;
    float x,y,rad;
    void program(){
        if(bg1>bg2){
            bg2+=3;
            y+=0.5;
            if(bg1<bg2)bg2=bg1;
            SetFont("nicoca_v1.ttf", 20.0f);
            DrawText(FormatString("%03d", 100), Vector2(270, y-1), Color::black);
            DrawText(FormatString("%03d", 100), Vector2(270, y), Color::white);
        }
    }
};

Vector2 cloudPos;       //!< 雲の位置
Vector2 cannonPos;      //!< 砲台の位置
Vector2 bulletPos;      //!< 弾の位置
Rect    targetRect;     //!< ターゲットの矩形
class_score score;          //!< スコア


// ゲーム開始時に呼ばれる関数です。
void Start()
{
    cloudPos = Vector2(-320, 100);
    cannonPos = Vector2(-80, -150);
    targetRect = Rect(80, -140, 40, 40);
    bulletPos.x = -999;
//    score = 0;
    
// BGMの再生
    PlayBGM("bgm_maoudamashii_8bit07.mp3");
    
    score.bg1 = 0;
    score.bg2 = 0;
}

// 1/60秒ごとに呼ばれる関数です。モデルの更新と画面の描画を行います。
void Update()
{
    // 弾の発射
    if (bulletPos.x <= -999 && Input::GetKeyDown(KeyMask::Space)) {
        PlaySound("se_maoudamashii_system20.mp3");      // SEの再生
        
        bulletPos = cannonPos + Vector2(50, 10);
    }

    // 弾の移動
    if (bulletPos.x > -999) {
        bulletPos.x += 10 * Time::deltaTime;

        // ターゲットと弾の当たり判定
        Rect bulletRect(bulletPos, Vector2(32, 20));
        if (targetRect.Overlaps(bulletRect)) {
            PlaySound("se_maoudamashii_explosion06.mp3");    // SEの再生
            score.bg1 += 100;         // スコアの加算
            score.y=-100;       //演出のリセット
            bulletPos.x = -999; // 弾を発射可能な状態に戻す
        }
    }

    // 背景の描画
    Clear(Color::cyan);
    FillRect(Rect(-320, -240, 640, 100), Color::green);

    // 雲の描画
    DrawImage("cloud1.png", cloudPos);

    // 弾の描画
    if (bulletPos.x > -999) {
        DrawImage("bullet.png", bulletPos);
    }

    // 砲台の描画
    FillRect(Rect(cannonPos.x-10, -140, 20, 100), Color::blue);
    DrawImage("cannon.png", cannonPos);

    // ターゲットの描画
    FillRect(targetRect, Color::red);

    // スコアの描画
    score.program();
    SetFont("nicoca_v1.ttf", 48.0f);
    DrawText(FormatString("%05d", score.bg2), Vector2(-319, 199), Color::black);
    DrawText(FormatString("%05d", score.bg2), Vector2(-320, 200), Color::white);
}

