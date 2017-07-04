//
//-----------------------------------------------------------------------------
//Filename:    Body.cpp
//-----------------------------------------------------------------------------
//
// Created by bonett_w on 7/3/17.
//-----------------------------------------------------------------------------
//

#include "Entities/Body.hpp"

const std::array<std::string, 4>      Body::_meshPlayers = {
        "Sinbad_green.mesh",
        "Sinbad_yellow.mesh",
        "Sinbad_blue.mesh",
        "Sinbad_red.mesh"
};


Body::Body(Map *map, Ogre::SceneManager *sceneManager, const std::string &name, int id)
        : _name(name), _bombPower(1), _maxBombs(1), _alive(true),
          _pos(Ogre::Vector2::ZERO),
          _dir(Ogre::Vector2::ZERO),
          _speed(100),
          _map(map),
          _wantBomb(false)
{
    if (sceneManager == nullptr)
        throw std::runtime_error("Player Manager Error");

    _nodeRoot = sceneManager->getRootSceneNode()->createChildSceneNode(name + "_root");
    _nodeBody = _nodeRoot->createChildSceneNode(name + "_body");
    _nodeHead = _nodeRoot->createChildSceneNode(name + "_head");

    _entityBody = sceneManager->createEntity(_meshPlayers[id]);

    _nodeBody->attachObject(_entityBody);
    _nodeBody->setScale(Ogre::Vector3(3, 4, 3));
}

Body::~Body() {
  _nodeBody->detachObject(_entityBody);
}

void Body::update(Ogre::Real elapsedTime) {
}

Ogre::SceneNode *Body::getNodeRoot() {
    return _nodeRoot;
}

Bomb*   Body::putNewBomb(Ogre::SceneManager* mgr, const Ogre::Vector2& pos, const Map& map)
{
  Bomb  *newBomb = nullptr;

  if (_bombs.size() < _maxBombs) {
    for (auto i = _bombs.begin() ; i != _bombs.end() ; ++i) {
      if ((*i)->getPos() == pos)
        return (nullptr);
    }
    newBomb = new Bomb(mgr, pos, map, _bombPower, this);
    _bombs.push_back(newBomb);
  }
  return (newBomb);
}

void    Body::removeBomb(void)
{
  _bombs.erase(_bombs.begin());
}

void  Body::receiveExplosion(void)
{
  //player die or something like that ...
  std::cerr << "AH !AH !AH !AH !AH !AH !AH !AH !AH !AH !AH !AH !AH !AH !AH !AH !AH !AH !AH !" << std::endl;
  _alive = false;
}

bool    Body::isAlive(void) const
{
  return (_alive);
}

const Ogre::Vector2 &Body::getPos() const {
    return _pos;
}

void Body::setPos(const Ogre::Vector2 &_pos) {
    Body::_pos = _pos;
}

const Ogre::Vector2 &Body::getDir() const {
    return _dir;
}

void Body::setDir(const Ogre::Vector2 &_dir) {
    Body::_dir = _dir;
}

Ogre::Real Body::getSpeed() const {
    return _speed;
}

void Body::setSpeed(Ogre::Real _speed) {
    Body::_speed = _speed;
}

void Body::setWantBomb(bool value) {
    _wantBomb = value;
}

bool Body::getWantBomb() const {
    return _wantBomb;
}

Body::CaseSearch Body::lookFast(void) const {
    CaseSearch st;

    std::memset(&st, 0, sizeof(st));
    if (_pos.x - 1 > 0)
        st.member.left = (int) _map->accessGrid()[_pos.y][_pos.x - 1];
    if (_pos.x + 1 < _map->getWidth())
        st.member.right = (int) _map->accessGrid()[_pos.y][_pos.x + 1];
    if (_pos.y - 1 > 0)
        st.member.up = (int) _map->accessGrid()[_pos.y][_pos.x - 1];
    if (_pos.y + 1 < _map->getWidth())
        st.member.down = (int) _map->accessGrid()[_pos.y][_pos.x + 1];
    return st;
}
