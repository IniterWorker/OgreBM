//
//-----------------------------------------------------------------------------
//Filename:    SplashState.cpp
//-----------------------------------------------------------------------------
//
// Created by bonett_w on 7/3/17.
//-----------------------------------------------------------------------------
//

#include "States/SplashState.hpp"

SplashState::SplashState() {

}

void SplashState::enter() {

}

void SplashState::createScene() {

}

void SplashState::exit() {

}

bool SplashState::keyPressed(const OIS::KeyEvent &keyEventRef) {
    return false;
}

bool SplashState::keyReleased(const OIS::KeyEvent &keyEventRef) {
    return false;
}

bool SplashState::mouseMoved(const OIS::MouseEvent &evt) {
    return false;
}

bool SplashState::mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id) {
    return false;
}

bool SplashState::mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id) {
    return false;
}

void SplashState::buttonHit(OgreBites::Button *button) {
    // SdkTrayListener::buttonHit(button);
}

void SplashState::update(Ogre::Real timeSinceLastFrame) {

}
