//
//-----------------------------------------------------------------------------
//Filename:    Game.cpp
//-----------------------------------------------------------------------------
//
// Created by bonett_w on 7/3/17.
//-----------------------------------------------------------------------------
//

#include "Game/Game.hpp"

Game::Game(Ogre::SceneManager *sceneManager) : _sceneManager(sceneManager) {
    _map = new Map(sceneManager, 10, 10);
}

Game::~Game() {
    delete _map;
    _map = nullptr;
}

void Game::update(Ogre::Real elapsedTime) {

}

Map *Game::getMap() {
    return _map;
}

std::vector<Player *> &Game::getPlayers() {
    return _vPlayers;
}
