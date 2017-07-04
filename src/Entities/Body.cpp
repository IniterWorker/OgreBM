//
//-----------------------------------------------------------------------------
//Filename:    Body.cpp
//-----------------------------------------------------------------------------
//
// Created by bonett_w on 7/3/17.
//-----------------------------------------------------------------------------
//

#include "Entities/Body.hpp"

Body::Body(Ogre::SceneManager *sceneManager, const std::string &name) : _name(name), _bombPower(1), _maxBombs(1)
{
    if (sceneManager == nullptr)
        throw std::runtime_error("Player Manager Error");

    _nodeRoot = sceneManager->getRootSceneNode()->createChildSceneNode(name + "_root");
    _nodeBody = _nodeRoot->createChildSceneNode(name + "_body");
    _nodeHead = _nodeRoot->createChildSceneNode(name + "_head");

    _entityBody = sceneManager->createEntity("ogrehead.mesh");

    _nodeBody->attachObject(_entityBody);
}

Body::~Body() {

}

void Body::update(Ogre::Real elapsedTime) {

}

Ogre::SceneNode *Body::getNodeRoot() {
    return _nodeRoot;
}

Ogre::Vector2&    Body::getPos(void)
{
  return (_pos);
}

Bomb*   Body::putNewBomb(Ogre::SceneManager* mgr, const Ogre::Vector2& pos, const Map& map)
{
  Bomb  *newBomb = nullptr;

  if (_bombs.size() < _maxBombs) {
    newBomb = new Bomb(mgr, pos, map, _bombPower, this);
    _bombs.push_back(newBomb);
  }
  return (newBomb);
}

void    Body::removeBomb(void)
{
  _bombs.erase(_bombs.begin());
}
