//
//-----------------------------------------------------------------------------
//Filename:    Player.hpp
//-----------------------------------------------------------------------------
//
// Created by bonett_w on 7/3/17.
//-----------------------------------------------------------------------------
//

#ifndef OGREBM_BODY_HPP
#define OGREBM_BODY_HPP

#include <OGRE/OgreTimer.h>
#include <OGRE/OgreSceneManager.h>
#include <OGRE/OgreEntity.h>
#include <string>
# include <vector>
# include "Entities/Bomb.hpp"
# include <OgreVector2.h>
#include <Game/InputController.hpp>

class Bomb;

class Body : public InputController {
protected:
  int           _bombPower;
  int           _maxBombs;
  std::vector<Bomb*>    _bombs;
    std::string _name;
    Ogre::SceneNode *_nodeRoot;
    Ogre::SceneNode *_nodeHead;
    Ogre::SceneNode *_nodeBody;
    Ogre::Entity *_entityHead;
    Ogre::Entity *_entityBody;
  Ogre::Vector2 _pos;
public:
    Body(Ogre::SceneManager *sceneManager, const std::string &name);

    virtual ~Body();

    virtual void update(Ogre::Real elapsedTime);

    Ogre::SceneNode *getNodeRoot();

  Ogre::Vector2&        getPos(void);

  Bomb  *putNewBomb(Ogre::SceneManager*, const Ogre::Vector2&, const Map&);
  void  removeBomb(void);
};


#endif //OGREBM_BODY_HPP
