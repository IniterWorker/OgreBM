//
//-----------------------------------------------------------------------------
//Filename:    Game.cpp
//-----------------------------------------------------------------------------
//
// Created by bonett_w on 7/3/17.
//-----------------------------------------------------------------------------
//

#include "Game/Game.hpp"

Game::Game(Ogre::RenderWindow *renderWindow, Ogre::SceneManager *sceneManager) :
        _renderWindow(renderWindow),
        _sceneManager(sceneManager) {
    _map = new Map(sceneManager, 10, 10);
}

Game::~Game() {
    delete _map;
    _map = nullptr;
}

void Game::update(Ogre::Real elapsedTime) {

    // Inject elapsedTime in all players
    for (auto it = _vPlayers.begin(); it != _vPlayers.end(); ++it) {
        (*it)->update(elapsedTime);
    }

    // Inject elapsedTime in all bombs
}

Map *Game::getMap() {
    return _map;
}

std::vector<Player *> &Game::getPlayers() {
    return _vPlayers;
}
