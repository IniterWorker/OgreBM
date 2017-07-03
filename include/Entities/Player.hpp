//
//-----------------------------------------------------------------------------
//Filename:    Player.hpp
//-----------------------------------------------------------------------------
//
// Created by bonett_w on 7/3/17.
//-----------------------------------------------------------------------------
//

#ifndef OGREBM_PLAYER_HPP
#define OGREBM_PLAYER_HPP

#include <OGRE/OgreTimer.h>
#include <OGRE/OgreSceneManager.h>
#include <string>

class Player {
protected:
    std::string _name;
    Ogre::SceneNode *_nodeRoot;
    Ogre::SceneNode *_nodeHead;
    Ogre::SceneNode *_nodeBody;
    Ogre::Entity *_entityHead;
    Ogre::Entity *_entityBody;
public:
    Player(Ogre::SceneManager *sceneManager, const std::string &name);

    virtual ~Player();

    virtual void moveUp();

    virtual void moveDown();

    virtual void moveLeft();

    virtual void moveRight();

    virtual void hitBomb();

    virtual void newBomb();
};


#endif //OGREBM_PLAYER_HPP
