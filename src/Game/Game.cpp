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
    InputController::ActionPlayer action;
    for (auto it = _vPlayers.begin(); it != _vPlayers.end(); ++it) {
        (*it)->update(elapsedTime);
        if ((*it)->getLastAction(action)) {
            // execute action
            auto move = (*it)->getNodeRoot()->getPosition();
            move.x += 100;
            (*it)->getNodeRoot()->setPosition(move);
        }
    }

    // Inject elapsedTime in all bombs
}

Map *Game::getMap() {
    return _map;
}

std::vector<Body *> &Game::getPlayers() {
    return _vPlayers;
}

void Game::addPlayer(Player *player) {
    _vPlayers.push_back(static_cast<Body *>(player));
}
