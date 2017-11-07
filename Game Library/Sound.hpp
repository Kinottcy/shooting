//
//  Sound.hpp
//  Game Framework
//
//  Created by numata on July 23, 2009.
//  Copyright (c) 2009-2016 Satoshi Numata. All rights reserved.
//

#ifndef __SOUND_HPP__
#define __SOUND_HPP__


#include "GMObject.hpp"
#include "Types.hpp"
#include "GameError.hpp"
#include <string>


void __InitSound();


/*!
    @class  Sound
    @group  Audio
    <p>ゲームの効果音を再生するためのクラスです。</p>
 
    <h3>複数回の再生について</h3>
    <p>再生中に Play() 関数を呼んだ場合、その再生は中断され、冒頭から再生が再開されます。</p>

    <h3>3次元の音場操作について</h3>
    <p>このクラスでは、3次元の音場に1人の聴取者（リスナ）と、複数の音源（ソース）があるものとしてモデル化されています。
    ひとつひとつのソースの位置は移動させることができ、それぞれの位置に応じて聞こえ方が変化します。またリスナの位置や向きも変化させることができます。</p>
 */
class Sound : public GMObject
{
private:
    std::string mFileName;
    void*       mSoundImpl;
    Vector3   mSourcePos;
    bool        mDoLoop;

public:
    /*!
        @task コンストラクタ
     */
    
    /*!
        @method Sound
        @abstract ファイル名（拡張子含む）を指定して、効果音再生用のサウンドを作成します。
        デフォルトではループ再生しませんが、第2引数に true を指定するとループ再生するようになります。
     */
    Sound(const std::string& filename, bool doLoop = false) throw (GameError);
    ~Sound();
    
public:
#pragma mark - Public 関数
    /*!
        @task   Public 関数
     */

    std::string GetFileName() const;

    /*!
        @method     GetPitch
        @abstract 現在設定されているピッチを取得します。
     */
    float       GetPitch() const;

    /*!
        @method     GetSourcePos
        このサウンドの3次元音場での再生位置を取得します。
     */
    Vector3     GetSourcePos() const;

    /*!
        @method     GetVolume
        現在設定されている音量を取得します。
     */
    float       GetVolume() const;

    /*!
        @method     IsPlaying
        このサウンドが再生中かどうかをリターンします。
     */
    bool        IsPlaying() const;

    /*!
        @method     Play
        @abstract サウンドの再生を開始します。
        このサウンドがすでに再生済みであった場合には、その再生が中断され、頭から再生が再開されます。
     */
    void        Play();

    /*!
        @method     Stop
        @abstract サウンドの再生を中断します。
     */
    void        Stop();
    
    /*!
        @method     SetPitch
        @abstract ピッチを設定します。
        <p>動作が保証されている値の範囲は、0.5〜2.0 です。</p>
        <p>デフォルトで設定されている値は 1.0 で、これが通常の再生速度となります。</p>
     */
    void        SetPitch(float value);
    
    /*!
        @method     SetSourcePos
        このサウンドの3次元音場での再生位置を設定します。
     */
    void        SetSourcePos(const Vector3& vec3);
    
    /*!
        @method     SetVolume
        音量を設定します。
     */
    void        SetVolume(float value);


    std::string ToString() const override;

public:
    /*!
        @task 3次元音場の操作（リスナの操作）
     */
    
    /*!
        @method     GetListenerHorizontalOrientation
        水平線上でのリスナの向きを取得します。
     */
    static float    GetListenerHorizontalOrientation();
    
    /*!
        @method     GetListenerPos
        3次元空間上でのリスナの現在位置を取得します。
     */
    static Vector3  GetListenerPos();
    
    /*!
        @method     SetListenerHorizontalOrientation
        水平線上でのリスナの向きを設定します。
     */
    static void     SetListenerHorizontalOrientation(float radAngle);
    
    /*!
        @method     SetListenerPos
        3次元空間上でのリスナの現在位置を設定します。
     */
    static void     SetListenerPos(float x, float y, float z);
    
    /*!
        @method     SetListenerPos
        3次元空間上でのリスナの現在位置を設定します。
     */
    static void     SetListenerPos(const Vector3& vec3);
        

};


#endif  //#ifndef __SOUND_HPP__

