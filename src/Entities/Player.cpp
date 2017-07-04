//
//-----------------------------------------------------------------------------
//Filename:    Player.cpp
//-----------------------------------------------------------------------------
//
// Created by bonett_w on 7/3/17.
//-----------------------------------------------------------------------------
//

#include "Entities/Player.hpp"

Player::Player(Ogre::SceneManager *sceneManager, const std::string &name) : Body(sceneManager, name) {}

bool Player::keyPressed(const OIS::KeyEvent &arg) {
  switch (arg.key) {
  case OIS::KC_UP:
    moveUp();
    break;
  case OIS::KC_DOWN:
    moveDown();
    break;
  case OIS::KC_LEFT:
    moveRight();
    break;
  case OIS::KC_RIGHT:
    moveLeft();
    break;
  case OIS::KC_SPACE:
    putBomb();
    break;
  }
  return false;
}

bool Player::keyReleased(const OIS::KeyEvent &arg) {
    if (_qInput.size())
        _qInput.pop();
    return false;
}
