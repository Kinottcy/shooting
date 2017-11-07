//
//  Input.hpp
//  Game Framework
//
//  Created by numata on Dec 27, 2010.
//  Copyright (c) 2010-2016 Satoshi Numata. All rights reserved.
//


#ifndef __INPUT_HPP__
#define __INPUT_HPP__

#include "GMObject.hpp"
#include "Types.hpp"
#include <map>
#include <set>


// 64キーまでサポート
typedef unsigned long long  KeyMaskType;


struct KeyMask {

    /*!
        @const UpArrow
        @group System
        上向きの矢印キーを表す定数です。
     */
    static const KeyMaskType UpArrow;

    /*!
        @const DownArrow
        @group System
        下向きの矢印キーを表す定数です。
     */
    static const KeyMaskType DownArrow;

    /*!
        @const LeftArrow
        @group System
        左向きの矢印キーを表す定数です。
     */
    static const KeyMaskType LeftArrow;

    /*!
        @const RightArrow
        @group System
        右向きの矢印キーを表す定数です。
     */
    static const KeyMaskType RightArrow;

    /*!
        @const Space
        @group System
        スペースキーを表す定数です。
     */
    static const KeyMaskType Space;

    /*!
        @const Escape
        @group System
        escキーを表す定数です。
     */
    static const KeyMaskType Escape;

    /*!
        @const Return
        @group System
        returnキーを表す定数です。
     */
    static const KeyMaskType Return;

    /*!
        @const Backspace
        @group System
        backspaceキーを表す定数です。
     */
    static const KeyMaskType Backspace;

    /*!
        @const Delete
        @group System
        deleteキーを表す定数です。
     */
    static const KeyMaskType Delete;

    /*!
        @const Tab
        @group System
        tabキーを表す定数です。
     */
    static const KeyMaskType Tab;

    /*!
        @const LeftShift
        @group System
        左側のshiftキーを表す定数です。
     */
    static const KeyMaskType LeftShift;

    /*!
        @const RightShift
        @group System
        右側のshiftキーを表す定数です。
     */
    static const KeyMaskType RightShift;

    /*!
        @const A
        @group System
        Aキーを表す定数です。
     */
    static const KeyMaskType A;

    /*!
        @const B
        @group System
        Bキーを表す定数です。
     */
    static const KeyMaskType B;

    /*!
        @const C
        @group System
        Cキーを表す定数です。
     */
    static const KeyMaskType C;

    /*!
        @const D
        @group System
        Dキーを表す定数です。
     */
    static const KeyMaskType D;

    /*!
        @const E
        @group System
        Eキーを表す定数です。
     */
    static const KeyMaskType E;

    /*!
        @const F
        @group System
        Fキーを表す定数です。
     */
    static const KeyMaskType F;

    /*!
        @const G
        @group System
        Gキーを表す定数です。
     */
    static const KeyMaskType G;

    /*!
        @const H
        @group System
        Hキーを表す定数です。
     */
    static const KeyMaskType H;

    /*!
        @const I
        @group System
        Iキーを表す定数です。
     */
    static const KeyMaskType I;

    /*!
        @const J
        @group System
        Jキーを表す定数です。
     */
    static const KeyMaskType J;

    /*!
        @const K
        @group System
        Kキーを表す定数です。
     */
    static const KeyMaskType K;

    /*!
        @const L
        @group System
        Lキーを表す定数です。
     */
    static const KeyMaskType L;

    /*!
        @const M
        @group System
        Mキーを表す定数です。
     */
    static const KeyMaskType M;

    /*!
        @const N
        @group System
        Nキーを表す定数です。
     */
    static const KeyMaskType N;

    /*!
        @const O
        @group System
        Oキーを表す定数です。
     */
    static const KeyMaskType O;

    /*!
        @const P
        @group System
        Pキーを表す定数です。
     */
    static const KeyMaskType P;

    /*!
        @const Q
        @group System
        Qキーを表す定数です。
     */
    static const KeyMaskType Q;

    /*!
        @const R
        @group System
        Rキーを表す定数です。
     */
    static const KeyMaskType R;

    /*!
        @const S
        @group System
        Sキーを表す定数です。
     */
    static const KeyMaskType S;

    /*!
        @const T
        @group System
        Tキーを表す定数です。
     */
    static const KeyMaskType T;

    /*!
        @const U
        @group System
        Uキーを表す定数です。
     */
    static const KeyMaskType U;

    /*!
        @const V
        @group System
        Vキーを表す定数です。
     */
    static const KeyMaskType V;

    /*!
        @const W
        @group System
        Wキーを表す定数です。
     */
    static const KeyMaskType W;

    /*!
        @const X
        @group System
        Xキーを表す定数です。
     */
    static const KeyMaskType X;

    /*!
        @const Y
        @group System
        Yキーを表す定数です。
     */
    static const KeyMaskType Y;

    /*!
        @const Z
        @group System
        Zキーを表す定数です。
     */
    static const KeyMaskType Z;

    /*!
        @const Alpha0
        @group System
        アルファベット列の上にある数字の0キーを表す定数です。
     */
    static const KeyMaskType Alpha0;

    /*!
        @const Alpha1
        @group System
        アルファベット列の上にある数字の1キーを表す定数です。
     */
    static const KeyMaskType Alpha1;

    /*!
        @const Alpha2
        @group System
        アルファベット列の上にある数字の2キーを表す定数です。
     */
    static const KeyMaskType Alpha2;

    /*!
        @const Alpha3
        @group System
        アルファベット列の上にある数字の3キーを表す定数です。
     */
    static const KeyMaskType Alpha3;
    
    /*!
        @const Alpha4
        @group System
        アルファベット列の上にある数字の4キーを表す定数です。
     */
    static const KeyMaskType Alpha4;
    
    /*!
        @const Alpha5
        @group System
        アルファベット列の上にある数字の5キーを表す定数です。
     */
    static const KeyMaskType Alpha5;
    
    /*!
        @const Alpha6
        @group System
        アルファベット列の上にある数字の6キーを表す定数です。
     */
    static const KeyMaskType Alpha6;
    
    /*!
        @const Alpha7
        @group System
        アルファベット列の上にある数字の7キーを表す定数です。
     */
    static const KeyMaskType Alpha7;
    
    /*!
        @const Alpha8
        @group System
        アルファベット列の上にある数字の8キーを表す定数です。
     */
    static const KeyMaskType Alpha8;
    
    /*!
        @const Alpha9
        @group System
        アルファベット列の上にある数字の9キーを表す定数です。
     */
    static const KeyMaskType Alpha9;

    /*!
        @const Keypad0
        @group System
        テンキーの0を表す定数です。
     */
    static const KeyMaskType Keypad0;
    
    /*!
        @const Keypad1
        @group System
        テンキーの1を表す定数です。
     */
    static const KeyMaskType Keypad1;
    
    /*!
        @const Keypad2
        @group System
        テンキーの2を表す定数です。
     */
    static const KeyMaskType Keypad2;
    
    /*!
        @const Keypad3
        @group System
        テンキーの3を表す定数です。
     */
    static const KeyMaskType Keypad3;
    
    /*!
        @const Keypad4
        @group System
        テンキーの4を表す定数です。
     */
    static const KeyMaskType Keypad4;
    
    /*!
        @const Keypad5
        @group System
        テンキーの5を表す定数です。
     */
    static const KeyMaskType Keypad5;
    
    /*!
        @const Keypad6
        @group System
        テンキーの6を表す定数です。
     */
    static const KeyMaskType Keypad6;
    
    /*!
        @const Keypad7
        @group System
        テンキーの7を表す定数です。
     */
    static const KeyMaskType Keypad7;
    
    /*!
        @const Keypad8
        @group System
        テンキーの8を表す定数です。
     */
    static const KeyMaskType Keypad8;
    
    /*!
        @const Keypad9
        @group System
        テンキーの9を表す定数です。
     */
    static const KeyMaskType Keypad9;

    /*!
        @const Any
        @group System
        あらゆるキーのマスクを表す定数です。
     */
    static const KeyMaskType Any;

    // TODO: マウスをマスク定数でサポートする。
};



/*!
    @class      Input
    @group      System
    @abstract   キーボードとマウスの入力を管理するためのクラスです。
 */
class Input : public GMObject
{
    static KeyMaskType  sKeyState;
    static KeyMaskType  sKeyStateOld;
    static KeyMaskType  sKeyDownStateTriggered;
    static KeyMaskType  sKeyUpStateTriggered;
    
    static bool         sIsMouseDown;
    static bool         sIsMouseDownOld;
    static bool         sIsMouseDownTriggered;
    static bool         sIsMouseUpTriggered;
    
    static bool         sIsMouseDownRight;
    static bool         sIsMouseDownOldRight;
    static bool         sIsMouseDownTriggeredRight;
    static bool         sIsMouseUpTriggeredRight;

public:
    static float    GetAxis(const std::string& axisName);
    static float    GetAxisRaw(const std::string& axisName);
    static void     ResetInputAxes();

    /*!
        @task   キーボードの管理
     */

    static bool     GetKey(KeyMaskType keyMask);
    static bool     GetKeyDown(KeyMaskType keyMask);
    static bool     GetKeyUp(KeyMaskType keyMask);

    
    /*!
        @task   マウスの管理
     */
    static bool     GetMouseButton(int button);
    static bool     GetMouseButtonDown(int button);
    static bool     GetMouseButtonUp(int button);
    
    /*!
        @method     MousePosition
        マウスの現在のカーソル位置を取得します。
     */
    static Vector2  MousePosition();


public:
    static void __ProcessKeyDown(KeyMaskType mask);
    static void __ProcessKeyUp(KeyMaskType mask);
    static void __ProcessMouseDown();
    static void __ProcessMouseUp();
    static void __ProcessMouseDownRight();
    static void __ProcessMouseUpRight();
    static void __UpdateTriggers();
};


#endif  //#ifndef __INPUT_HPP__


