#ifndef __SETTINGS_HPP__
#define __SETTINGS_HPP__


// ※ Settings.hppの定数を変更するたびに、Xcodeのメニューから[Product]-[Clean]を実行してください。


// アニメーションの更新レート
#define FRAME_RATE              60.0f

// ポリゴン描画のバッチ処理サイズ
#define DRAW_BATCH_SIZE         1024

// タイトル文字列（ウィンドウのタイトルのみ。その他の箇所のタイトル文字列の変更は、MainMenu.xib とターゲットの設定で行う。）
#define GAME_TITLE              "Game"

// 画面サイズ
#define SCREEN_SIZE             Vector2(640, 480)


#endif  //#ifndef __SETTINGS_HPP__

