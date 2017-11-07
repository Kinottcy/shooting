//
//  GMGame.hpp
//  Game Framework
//
//  Created by numata on Jan 04, 2011.
//  Copyright (c) 2011-2016 Satoshi Numata. All rights reserved.
//

#ifndef __GM_GAME_HPP__
#define __GM_GAME_HPP__


#include "GMObject.hpp"
#include "Color.hpp"
#include "Input.hpp"
#include "Camera.hpp"
#include "BaseRenderer.hpp"
#include "Music.hpp"
#include "Sound.hpp"
#include "XmlDocument.hpp"
#include <map>
#include <string>


/*!
    @class  GMGame
    @group  System
    @abstract ゲームの基本設定の確認とシーン管理の機能を提供するためのクラスです。
 */
class GMGame : public GMObject
{
    Color       mStartUpColor;
    std::string mTitle;

private:
    std::map<std::string, Sound*>   soundMap;
    std::map<std::string, Music*>   musicMap;
    std::map<std::string, Texture*> textureMap;

public:
    BaseRenderer*   renderer;
    Camera*         camera;

public:
    static GMGame* GetInstance();
    GMGame();
    void    SetUp();
    virtual ~GMGame();
    
protected:
    void        SetStartUpColor(const Color& color);
    void        SetTitle(const std::string& str);
    
public:
    /*!
        @task ゲームの基本設定
     */

    /*!
        @method     getStartUpColor
        @abstract   特定シーンの drawView() メソッドが呼ばれる前の起動時の画面を塗り潰すための色を取得します。
        この色は、Globals.h の STARTUP_COLOR マクロで設定してください。
     */
    Color     GetStartUpColor() const;

    /*!
        @method     getTitle
        @abstract   このゲームのウィンドウのタイトルバーに表示されているタイトル文字列を取得します。
     */
    std::string GetTitle() const;
    
public:
    ///// ゲーム進行
    void        Render();

public:
    Music*          LoadMusic(const std::string& filename, bool loop=true);
    Sound*          LoadSound(const std::string& filename, bool loop=false);
    Texture*        LoadTexture(const std::string& filename);

};

#endif  //#ifndef __GM_GAME_HPP__


