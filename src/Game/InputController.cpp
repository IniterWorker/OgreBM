//
//-----------------------------------------------------------------------------
//Filename:    InputController.cpp
//-----------------------------------------------------------------------------
//
// Created by bonett_w on 7/3/17.
//-----------------------------------------------------------------------------
//

#include <OgreFramework.hpp>
#include "Game/InputController.hpp"

InputController::InputController() : _qInput() {

}

InputController::~InputController() {

}

void InputController::moveUp() {
    _qInput.push(ActionPlayer::GO_UP);
    OgreFramework::getSingletonPtr()->_log->logMessage("GO_UP");
}

void InputController::moveDown() {
    _qInput.push(ActionPlayer::GO_DOWN);
    OgreFramework::getSingletonPtr()->_log->logMessage("GO_DOWN");
}

void InputController::moveRight() {
    _qInput.push(ActionPlayer::GO_RIGHT);
}

void InputController::moveLeft() {
    _qInput.push(ActionPlayer::GO_LEFT);
}

void InputController::putBomb() {
    _qInput.push(ActionPlayer::PUT_BOMB);
}

void InputController::hitBomb() {
    _qInput.push(ActionPlayer::HIT_BOMB);
}

bool InputController::getLastAction(InputController::ActionPlayer &action) {
    if (_qInput.size() == 0)
        return false;

    action = _qInput.front();
    return true;
}
