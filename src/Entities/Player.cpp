//
//-----------------------------------------------------------------------------
//Filename:    Player.cpp
//-----------------------------------------------------------------------------
//
// Created by bonett_w on 7/3/17.
//-----------------------------------------------------------------------------
//

#include "Entities/Player.hpp"

Player::Player(Map *map, Ogre::SceneManager *sceneManager, const std::string &name, int id)
        : Body(map, sceneManager, name, id) {}

bool Player::keyPressed(const OIS::KeyEvent &arg) {
    switch (arg.key) {
        case OIS::KC_UP:
            _dir.x = -1;
            break;
        case OIS::KC_DOWN:
            _dir.x = 1;
            break;
        case OIS::KC_LEFT:
            _dir.y = 1;
            break;
        case OIS::KC_RIGHT:
            _dir.y = -1;
            break;
        case OIS::KC_SPACE:
            setWantBomb(true);
            break;
    }
    return false;
}

bool Player::keyReleased(const OIS::KeyEvent &arg) {
    switch (arg.key) {
        case OIS::KC_UP:
            _dir.x = 0;
            break;
        case OIS::KC_DOWN:
            _dir.x = 0;
            break;
        case OIS::KC_LEFT:
            _dir.y = 0;
            break;
        case OIS::KC_RIGHT:
            _dir.y = 0;
            break;
    }
    return false;
}
