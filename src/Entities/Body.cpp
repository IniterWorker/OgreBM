//
//-----------------------------------------------------------------------------
//Filename:    Body.cpp
//-----------------------------------------------------------------------------
//
// Created by bonett_w on 7/3/17.
//-----------------------------------------------------------------------------
//

#include "Entities/Body.hpp"

Body::Body(Ogre::SceneManager *sceneManager, const std::string &name) : _name(name) {
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
