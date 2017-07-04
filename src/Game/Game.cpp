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
  _map = new Map(sceneManager, 15, 15);
}

Game::~Game() {
    delete _map;
    _map = nullptr;
}

void Game::update(Ogre::Real elapsedTime) {

    // Inject elapsedTime in all players
    InputController::ActionPlayer action;
    for (auto i = _vBombs.begin() ; i != _vBombs.end() ; ++i) {
      if ((*i)->update(elapsedTime, *_map)) {
        delete (*i);
        _vBombs.erase(i);
        break;
      }
    }
    for (auto it = _vPlayers.begin(); it != _vPlayers.end(); ++it) {
        (*it)->update(elapsedTime);
        if ((*it)->getLastAction(action)) {
            // execute action
            auto move = (*it)->getNodeRoot()->getPosition();
            Ogre::Vector2 pos = (*it)->getPos();
            switch (action) {
            case InputController::ActionPlayer::GO_UP:
              move.x -= _map->getBlocDim().x;
              pos.x--;
              (*it)->getNodeRoot()->resetOrientation();
              (*it)->getNodeRoot()->yaw(Ogre::Radian(-M_PI / 2));
              break;
            case InputController::ActionPlayer::GO_DOWN:
              move.x += _map->getBlocDim().x;
              pos.x++;
              (*it)->getNodeRoot()->resetOrientation();
              (*it)->getNodeRoot()->yaw(Ogre::Radian(M_PI / 2));
              break;
            case InputController::ActionPlayer::GO_RIGHT:
              move.z += _map->getBlocDim().z;
              pos.y++;
              (*it)->getNodeRoot()->resetOrientation();
              break;
            case InputController::ActionPlayer::GO_LEFT:
              move.z -= _map->getBlocDim().z;
              pos.y--;
              (*it)->getNodeRoot()->resetOrientation();
              (*it)->getNodeRoot()->yaw(Ogre::Radian(-M_PI));
              break;
            case InputController::ActionPlayer::PUT_BOMB:
              Bomb *newBomb;
              if ((newBomb = (*it)->putNewBomb(_sceneManager, pos, *_map)))
                _vBombs.push_back(newBomb);
              break;
            default:
              break;
            }
            if (_map->accessGrid()[pos.y][pos.x] == Map::Bloc::EMPTY) {
              (*it)->getPos() = pos;
              (*it)->getNodeRoot()->setPosition(move);
            }
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
    _vPlayers.back()->getNodeRoot()->setPosition(_map->getStartEmplacement(_vPlayers.size() - 1));
    _vPlayers.back()->getPos() = _map->getStartPos(_vPlayers.size() - 1);
}
