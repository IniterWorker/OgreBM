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
#include <Game/InputController.hpp>

class Body : public InputController {
protected:
    std::string _name;
    Ogre::SceneNode *_nodeRoot;
    Ogre::SceneNode *_nodeHead;
    Ogre::SceneNode *_nodeBody;
    Ogre::Entity *_entityHead;
    Ogre::Entity *_entityBody;
public:
    Body(Ogre::SceneManager *sceneManager, const std::string &name);

    virtual ~Body();

    virtual void update(Ogre::Real elapsedTime);

    Ogre::SceneNode *getNodeRoot();
};


#endif //OGREBM_BODY_HPP
