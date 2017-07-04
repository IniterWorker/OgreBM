//
//-----------------------------------------------------------------------------
//Filename:    Game.cpp
//-----------------------------------------------------------------------------
//
// Created by bonett_w on 7/3/17.
//-----------------------------------------------------------------------------
//

#include <Entities/IA.hpp>
#include "Game/Game.hpp"

Game::Game(Ogre::RenderWindow *renderWindow, Ogre::SceneManager *sceneManager) :
        _renderWindow(renderWindow),
        _sceneManager(sceneManager) {
  _map = new Map(sceneManager, 15, 15);
  _mvCooldown = 0;
}

Game::~Game() {
    delete _map;
    _map = nullptr;
}

void Game::update(Ogre::Real elapsedTime) {

    // Inject elapsedTime in all players
    InputController::ActionPlayer action;
    _map->update(elapsedTime);
    for (auto i = _vBombs.begin() ; i != _vBombs.end() ; ++i) {
      if ((*i)->update(elapsedTime, *_map, _vBombs, _vPlayers)) {
        delete (*i);
        _vBombs.erase(i);
        break;
      }
    }
    _mvCooldown -= elapsedTime;
    for (auto it = _vPlayers.begin(); it != _vPlayers.end(); ++it) {
        (*it)->update(elapsedTime);
        auto move = (*it)->getNodeRoot()->getPosition();
        const Ogre::Vector2 dir = (*it)->getDir();
        const Ogre::Real speed = (*it)->getSpeed();

        if (dir == Ogre::Vector2::ZERO)
            continue;

        int posX = (int) (((move.x + _map->getBlocDim().x / 2) / _map->getBlocDim().x));
        int posY = (int) (((move.z + _map->getBlocDim().z / 2) / _map->getBlocDim().z));

        if (dir.x < 0) {
            move.x -= speed * elapsedTime;
            (*it)->getNodeRoot()->resetOrientation();
            (*it)->getNodeRoot()->yaw(Ogre::Radian(-M_PI / 2));
        }
        if (dir.x > 0) {
            move.x += speed * elapsedTime;
            (*it)->getNodeRoot()->resetOrientation();
            (*it)->getNodeRoot()->yaw(Ogre::Radian(M_PI / 2));
        }
        if (dir.y > 0) {
            move.z += speed * elapsedTime;
            (*it)->getNodeRoot()->resetOrientation();
        }
        if (dir.y < 0) {
            move.z -= speed * elapsedTime;
            (*it)->getNodeRoot()->resetOrientation();
            (*it)->getNodeRoot()->yaw(Ogre::Radian(-M_PI));
        }
        if ((*it)->getWantBomb()) {
            Bomb *newBomb;
            if ((newBomb = (*it)->putNewBomb(_sceneManager, {posX, posY}, *_map)))
                _vBombs.push_back(newBomb);
            (*it)->setWantBomb(false);
        }

        posX = (int) (((move.x + _map->getBlocDim().x / 2) / _map->getBlocDim().x));
        posY = (int) (((move.z + _map->getBlocDim().z / 2) / _map->getBlocDim().z));

        std::cout << "posX : " << posX << " posY " << posY << std::endl;

        bool isOnBomb = false;
        for (auto i = _vBombs.begin() ; i != _vBombs.end() ; ++i) {
          if (posX == (*i)->getPos().x
              && posX == (*i)->getPos().y
              && (*it)->getPos().x != posX
              && (*it)->getPos().y != posY) {
              isOnBomb = true;
              break;
          }
        }

        if (!isOnBomb && posX > 0 && posY > 0
            && posY < _map->getHeight() && posX < _map->getWidth()
            && _map->accessGrid()[posY][posX] == Map::Bloc::EMPTY) {
          (*it)->setPos({posX, posY});
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
    _vPlayers.back()->getNodeRoot()->setPosition(_map->getStartEmplacement(_vPlayers.size() - 1));
    _vPlayers.back()->setPos(_map->getStartPos(_vPlayers.size() - 1));
}

void Game::addIA(const std::string &name, const std::string &scriptPath) {
  IA *bot = new IA(_map, _sceneManager, name, scriptPath, _vPlayers.size());
    _vPlayers.push_back(static_cast<Body *>(bot));
    _vPlayers.back()->getNodeRoot()->setPosition(_map->getStartEmplacement(_vPlayers.size() - 1));
    _vPlayers.back()->setPos(_map->getStartPos(_vPlayers.size() - 1));
}
