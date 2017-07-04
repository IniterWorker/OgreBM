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
# include <array>

class Bomb;

class Map;

class Body {
protected:
    int _bombPower;
    int _maxBombs;
    bool _wantBomb;
    std::vector<Bomb *> _bombs;
    std::string _name;
    Ogre::SceneNode *_nodeRoot;
    Ogre::SceneNode *_nodeHead;
    Ogre::SceneNode *_nodeBody;
    Ogre::Entity *_entityHead;
    Ogre::Entity *_entityBody;
    Ogre::Vector2 _pos;
    Ogre::Vector2 _dir;
    Ogre::Real _speed;
    Map *_map;

    union CaseSearch {
      int data[4];
        struct {
            int left;
            int right;
            int up;
            int down;
        } member;
    };

    static const std::array<std::string, 4> _meshPlayers;

    bool _alive;

public:
    Body(Map *map, Ogre::SceneManager *sceneManager, const std::string &name, int id);

    virtual ~Body();

    virtual void update(Ogre::Real elapsedTime);

    Ogre::SceneNode *getNodeRoot();

    Bomb *putNewBomb(Ogre::SceneManager *, const Ogre::Vector2 &, const Map &);

    void removeBomb(void);

    void receiveExplosion(void);

    const Ogre::Vector2 &getPos() const;

    void setPos(const Ogre::Vector2 &_pos);

    const Ogre::Vector2 &getDir() const;

    void setDir(const Ogre::Vector2 &_dir);

    Ogre::Real getSpeed() const;

    void setSpeed(Ogre::Real _speed);

    void setWantBomb(bool value);

    bool getWantBomb() const;

    bool isAlive(void) const;

    CaseSearch lookFast(void) const;
};


#endif //OGREBM_BODY_HPP
