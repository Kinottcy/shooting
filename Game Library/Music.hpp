//
//  Music.hpp
//  Game Framework
//
//  Created by numata on July 23, 2009.
//  Copyright (c) 2009-2016 Satoshi Numata. All rights reserved.
//

#ifndef __MUSIC_HPP__
#define __MUSIC_HPP__

#include "GMObject.hpp"
#include "GameError.hpp"
#include <string>


/*!
    @class  Music
    @group  Audio
    <p>ゲームの BGM を再生するためのクラスです。</p>
 */
class Music : public GMObject
{    
private:
    std::string mFileName;
    void*       mAudioPlayer;
    bool        mDoLoop;
    bool        mIsPausing;
    int         mBGMID;
    
public:
    /*!
        @task コンストラクタ
     */
    
    /*!
        @method Music
        @abstract ファイル名（拡張子含む）を指定して、BGM再生用のインスタンスを作成します。
        デフォルトではループ再生しますが、第2引数に false を指定するとループ再生しないようになります。
     */
    Music(const std::string& filename, bool loop=true) throw (GameError);
    ~Music();
    
public:
    /*!
        @task Public 関数
     */

    std::string GetFileName() const;

    /*!
        @method     GetVolume
        @abstract   BGM の再生音量を取得します。
        @return BGM の再生音量
     */    
    float   GetVolume() const;

    /*!
        @method     IsPlaying
        @abstract   BGM が再生中かどうかを取得します。
        @return     BGM が再生中であれば true、そうでなければ false
     */    
    bool    IsPlaying() const;

    /*!
        @method     Pause
        @abstract   BGM の再生を一時停止します。
     */
    void    Pause();

    /*!
        @method     Play
        @abstract   BGM の再生を開始します。
     */
    void    Play();

    void    SetRate(float rate);

    /*!
        @method     SetVolume
        @abstract   BGM の再生音量を設定します。
     */    
    void    SetVolume(float value);

    /*!
        @method     Stop
        @abstract   BGM の再生を中断します。
        このメソッドの呼び出し後、BGM の再生位置は先頭に戻ります。
     */
    void    Stop();


    std::string ToString() const override;

};


#endif  //#ifndef __MUSIC_HPP__


