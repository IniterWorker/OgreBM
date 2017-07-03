//
//-----------------------------------------------------------------------------
//Filename:    AppState.cpp
//-----------------------------------------------------------------------------
//
//This source file is part of the
//
// Created by bonett_w on 6/9/17.
//-----------------------------------------------------------------------------
//

#include "States/AppState.hpp"

AppState *AppState::findByName(Ogre::String stateName) { return _pParent->findByName(stateName); }

void AppState::changeAppState(AppState *state) { _pParent->changeAppState(state); }

bool AppState::pushAppState(AppState *state) { return _pParent->pushAppState(state); }

void AppState::popAppState() { _pParent->popAppState(); }

void AppState::shutdown() { _pParent->shutdown(); }

void AppState::popAllAndPushAppState(AppState *state) { _pParent->popAllAndPushAppState(state); }

bool AppState::pause() {
    return true;
}

void AppState::resume() {

}
