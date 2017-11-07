//
//  GameError.hpp
//  Game Framework
//
//  Created by numata on Jan 03, 2011.
//  Copyright (c) 2011-2016 Satoshi Numata. All rights reserved.
//

#ifndef __GAME_ERROR_HPP__
#define __GAME_ERROR_HPP__


#include "GMObject.hpp"
#include <stdexcept>
#include <string>


/*!
    @class  GameError
    @group  Error Handling
 */
class GameError : public std::exception, public GMObject
{
protected:
    std::string     mMessage;
    
public:
    GameError() throw();
    GameError(const char* format, ...) throw();
    GameError(const std::string& message) throw();
    virtual ~GameError() throw();
    
public:
    // TODO: GameError::GetTitle()の文字列をアラートの表示に反映させる。
    virtual std::string GetTitle() const { return "Game Runtime Error"; };
    virtual const char* what() const throw() override { return mMessage.c_str(); };
    
};

/*!
    @class  GameArithmeticError
    @group  Error Handling
 */
class GameArithmeticError : public GameError
{
public:
    GameArithmeticError() throw();
    GameArithmeticError(const char* format, ...) throw();
    GameArithmeticError(const std::string& message) throw();
    
public:
    virtual std::string GetTitle() const override { return "Arithmetic Error"; }

};


/*!
    @class  GameInvalidOperationError
    @group  Error Handling
 */
class GameInvalidOperationError : public GameError
{
public:
    GameInvalidOperationError() throw();
    GameInvalidOperationError(const char* format, ...) throw();
    GameInvalidOperationError(const std::string& message) throw();
    
public:
    virtual std::string GetTitle() const override { return "Invalid Operation"; }
    
};


/*!
    @class  GameOutOfMemoryError
    @group  Error Handling
 */
class GameOutOfMemoryError : public GameError
{
public:
    GameOutOfMemoryError() throw();
    GameOutOfMemoryError(const char* format, ...) throw();
    GameOutOfMemoryError(const std::string& message) throw();
    
public:
    virtual std::string GetTitle() const override { return "Out of Memory"; }
    
};


#endif  //#ifndef __GAME_ERROR_HPP__


