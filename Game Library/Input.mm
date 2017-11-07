//
//  Input.mm
//  Game Framework
//
//  Created by numata on Dec 27, 2010.
//  Copyright (c) 2010-2016 Satoshi Numata. All rights reserved.
//

#include "Settings.hpp"
#include "Input.hpp"
#include <algorithm>
#include <utility>
#import "GMAppDelegate.hpp"
#include "Globals.hpp"


KeyMaskType Input::sKeyState = 0;
KeyMaskType Input::sKeyStateOld = 0;
KeyMaskType Input::sKeyDownStateTriggered = 0;
KeyMaskType Input::sKeyUpStateTriggered = 0;

bool Input::sIsMouseDown = false;
bool Input::sIsMouseDownOld = false;
bool Input::sIsMouseDownTriggered = false;
bool Input::sIsMouseUpTriggered = false;

bool Input::sIsMouseDownRight = false;
bool Input::sIsMouseDownOldRight = false;
bool Input::sIsMouseDownTriggeredRight = false;
bool Input::sIsMouseUpTriggeredRight = false;


const KeyMaskType KeyMask::UpArrow     = (1ULL << 0);
const KeyMaskType KeyMask::DownArrow   = (1ULL << 1);
const KeyMaskType KeyMask::LeftArrow   = (1ULL << 2);
const KeyMaskType KeyMask::RightArrow  = (1ULL << 3);
const KeyMaskType KeyMask::Space  = (1ULL << 4);
const KeyMaskType KeyMask::Escape = (1ULL << 5);
const KeyMaskType KeyMask::Return = (1ULL << 6);
const KeyMaskType KeyMask::Backspace = (1ULL << 7);
const KeyMaskType KeyMask::Delete = (1ULL << 8);
const KeyMaskType KeyMask::Tab = (1ULL << 9);
const KeyMaskType KeyMask::LeftShift  = (1ULL << 10);
const KeyMaskType KeyMask::RightShift  = (1ULL << 11);

const KeyMaskType KeyMask::A      = (1ULL << 15);
const KeyMaskType KeyMask::B      = (1ULL << 16);
const KeyMaskType KeyMask::C      = (1ULL << 17);
const KeyMaskType KeyMask::D      = (1ULL << 18);
const KeyMaskType KeyMask::E      = (1ULL << 19);
const KeyMaskType KeyMask::F      = (1ULL << 20);
const KeyMaskType KeyMask::G      = (1ULL << 21);
const KeyMaskType KeyMask::H      = (1ULL << 22);
const KeyMaskType KeyMask::I      = (1ULL << 23);
const KeyMaskType KeyMask::J      = (1ULL << 24);
const KeyMaskType KeyMask::K      = (1ULL << 25);
const KeyMaskType KeyMask::L      = (1ULL << 26);
const KeyMaskType KeyMask::M      = (1ULL << 27);
const KeyMaskType KeyMask::N      = (1ULL << 28);
const KeyMaskType KeyMask::O      = (1ULL << 29);
const KeyMaskType KeyMask::P      = (1ULL << 30);
const KeyMaskType KeyMask::Q      = (1ULL << 31);
const KeyMaskType KeyMask::R      = (1ULL << 32);
const KeyMaskType KeyMask::S      = (1ULL << 33);
const KeyMaskType KeyMask::T      = (1ULL << 34);
const KeyMaskType KeyMask::U      = (1ULL << 35);
const KeyMaskType KeyMask::V      = (1ULL << 36);
const KeyMaskType KeyMask::W      = (1ULL << 37);
const KeyMaskType KeyMask::X      = (1ULL << 38);
const KeyMaskType KeyMask::Y      = (1ULL << 39);
const KeyMaskType KeyMask::Z      = (1ULL << 40);

const KeyMaskType KeyMask::Alpha0       = (1ULL << 41);
const KeyMaskType KeyMask::Alpha1       = (1ULL << 42);
const KeyMaskType KeyMask::Alpha2       = (1ULL << 43);
const KeyMaskType KeyMask::Alpha3       = (1ULL << 44);
const KeyMaskType KeyMask::Alpha4       = (1ULL << 45);
const KeyMaskType KeyMask::Alpha5       = (1ULL << 46);
const KeyMaskType KeyMask::Alpha6       = (1ULL << 47);
const KeyMaskType KeyMask::Alpha7       = (1ULL << 48);
const KeyMaskType KeyMask::Alpha8       = (1ULL << 49);
const KeyMaskType KeyMask::Alpha9       = (1ULL << 50);

const KeyMaskType KeyMask::Keypad0       = (1ULL << 51);
const KeyMaskType KeyMask::Keypad1       = (1ULL << 52);
const KeyMaskType KeyMask::Keypad2       = (1ULL << 53);
const KeyMaskType KeyMask::Keypad3       = (1ULL << 54);
const KeyMaskType KeyMask::Keypad4       = (1ULL << 55);
const KeyMaskType KeyMask::Keypad5       = (1ULL << 56);
const KeyMaskType KeyMask::Keypad6       = (1ULL << 57);
const KeyMaskType KeyMask::Keypad7       = (1ULL << 58);
const KeyMaskType KeyMask::Keypad8       = (1ULL << 59);
const KeyMaskType KeyMask::Keypad9       = (1ULL << 60);

const KeyMaskType KeyMask::Any    = 0xffffffffffffffffULL;


static const int kAxisHistorySize = 10;
static float xAxisHistory[kAxisHistorySize];
static int xAxisHistoryPos = 0;
static float yAxisHistory[kAxisHistorySize];
static int yAxisHistoryPos = 0;


float Input::GetAxis(const std::string& axisName)
{
    if (axisName == "Horizontal") {
        float x = 0.0f;
        if (Input::GetKey(KeyMask::LeftArrow)) {
            x -= 1.0f;
        }
        if (Input::GetKey(KeyMask::RightArrow)) {
            x += 1.0f;
        }
        xAxisHistory[xAxisHistoryPos++] = x;
        if (xAxisHistoryPos >= kAxisHistorySize) {
            xAxisHistoryPos = 0;
        }
        float average = 0.0f;
        for (int i = 0; i < kAxisHistorySize; i++) {
            average += xAxisHistory[i];
        }
        average /= kAxisHistorySize;
        return average;
    } else if (axisName == "Vertical") {
        float y = 0.0f;
        if (Input::GetKey(KeyMask::DownArrow)) {
            y -= 1.0f;
        }
        if (Input::GetKey(KeyMask::UpArrow)) {
            y += 1.0f;
        }
        yAxisHistory[yAxisHistoryPos++] = y;
        if (yAxisHistoryPos >= kAxisHistorySize) {
            yAxisHistoryPos = 0;
        }
        float average = 0.0f;
        for (int i = 0; i < kAxisHistorySize; i++) {
            average += yAxisHistory[i];
        }
        average /= kAxisHistorySize;
        return average;
    } else {
        throw GameError("Input::GetAxis(): Unknown axis name: %s", axisName.c_str());
    }
}

float Input::GetAxisRaw(const std::string& axisName)
{
    if (axisName == "Horizontal") {
        float ret = 0.0f;
        if (Input::GetKey(KeyMask::LeftArrow)) {
            ret -= 1.0f;
        }
        if (Input::GetKey(KeyMask::RightArrow)) {
            ret += 1.0f;
        }
        return ret;
    } else if (axisName == "Vertical") {
        float ret = 0.0f;
        if (Input::GetKey(KeyMask::DownArrow)) {
            ret -= 1.0f;
        }
        if (Input::GetKey(KeyMask::UpArrow)) {
            ret += 1.0f;
        }
        return ret;
    } else {
        throw GameError("Input::GetAxisRaw(): Unknown axis name: %s", axisName.c_str());
    }
}

void Input::ResetInputAxes()
{
    for (int i = 0; i < kAxisHistorySize; i++) {
        xAxisHistory[i]= 0.0f;
        yAxisHistory[i]= 0.0f;
    }
}

bool Input::GetKey(KeyMaskType keyMask)
{
    return (sKeyState & keyMask)? true: false;
}

bool Input::GetKeyDown(KeyMaskType keyMask)
{
    return (sKeyDownStateTriggered & keyMask)? true: false;
}

bool Input::GetKeyUp(KeyMaskType keyMask)
{
    return (sKeyUpStateTriggered & keyMask)? true: false;
}


bool Input::GetMouseButton(int button)
{
    if (button == 0) {
        return sIsMouseDown;
    } else {
        return sIsMouseDownRight;
    }
}

bool Input::GetMouseButtonDown(int button)
{
    if (button == 0) {
        return sIsMouseDownTriggered;
    } else {
        return sIsMouseDownTriggeredRight;
    }
}

bool Input::GetMouseButtonUp(int button)
{
    if (button == 0) {
        return sIsMouseUpTriggered;
    } else {
        return sIsMouseUpTriggeredRight;
    }
}

Vector2 Input::MousePosition()
{
    NSWindow* window = [[GMAppDelegate sharedInstance] window];

    NSPoint location = [NSEvent mouseLocation];
    NSRect rect = NSMakeRect(location.x, location.y, 0.0f, 0.0f);
    rect = [window convertRectFromScreen:rect];
    location = rect.origin;
    return Vector2(location.x, location.y);
}

void Input::__ProcessKeyDown(KeyMaskType mask)
{
    sKeyState |= mask;
}

void Input::__ProcessKeyUp(KeyMaskType mask)
{
    sKeyState &= ~mask;
}

void Input::__ProcessMouseDown()
{
    sIsMouseDown = true;
}

void Input::__ProcessMouseUp()
{
    sIsMouseDown = false;
}

void Input::__ProcessMouseDownRight()
{
    sIsMouseDownRight = true;
}

void Input::__ProcessMouseUpRight()
{
    sIsMouseDownRight = false;
}

void Input::__UpdateTriggers()
{
    sKeyDownStateTriggered = sKeyState & ~sKeyStateOld;
    sKeyUpStateTriggered = ~sKeyState & sKeyStateOld;
	sKeyStateOld = sKeyState;
    
    sIsMouseDownTriggered = sIsMouseDown & ~sIsMouseDownOld;
    sIsMouseUpTriggered = ~sIsMouseDown & sIsMouseDownOld;
    sIsMouseDownOld = sIsMouseDown;

    sIsMouseDownTriggeredRight = sIsMouseDownRight & ~sIsMouseDownOldRight;
    sIsMouseUpTriggeredRight = ~sIsMouseDownRight & sIsMouseDownOldRight;
    sIsMouseDownOldRight = sIsMouseDownRight;
}

