//
//-----------------------------------------------------------------------------
//Filename:    Player.cpp
//-----------------------------------------------------------------------------
//
// Created by bonett_w on 7/3/17.
//-----------------------------------------------------------------------------
//

#include "Entities/Player.hpp"

Player::Player(Ogre::SceneManager *sceneManager, const std::string &name) : _name(name) {
    if (sceneManager == nullptr)
        throw std::runtime_error("Player Manager Error");

    _nodeRoot = sceneManager->getRootSceneNode()->createChildSceneNode();
    _nodeBody = _nodeRoot->createChildSceneNode();
    _nodeHead = _nodeRoot->createChildSceneNode();
}

Player::~Player() {

}

void Player::moveUp() {

}

void Player::moveDown() {

}

void Player::moveLeft() {

}

void Player::moveRight() {

}

void Player::hitBomb() {

}

void Player::newBomb() {

}

void Player::update(Ogre::Real elapsedTime) {

}
