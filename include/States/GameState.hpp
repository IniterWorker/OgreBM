//
//-----------------------------------------------------------------------------
//Filename:    GameState.hpp
//-----------------------------------------------------------------------------
//
// Created by bonett_w on 7/3/17.
//-----------------------------------------------------------------------------
//

#ifndef OGREBM_GAMESTATE_HPP
#define OGREBM_GAMESTATE_HPP

#include <OGRE/OgreSceneManager.h>
#include <OGRE/OgreSceneNode.h>
#include "AppState.hpp"

class GameState : public AppState {
public:
    GameState();

    DECLARE_APPSTATE_CLASS(GameState)

    void enter();

    void createScene();

    void exit();

    bool keyPressed(const OIS::KeyEvent &keyEventRef);

    bool keyReleased(const OIS::KeyEvent &keyEventRef);

    bool mouseMoved(const OIS::MouseEvent &evt);

    bool mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id);

    bool mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id);

    void buttonHit(OgreBites::Button *button);

    void update(Ogre::Real timeSinceLastFrame);

private:
    bool _isQuit;
    Ogre::SceneManager *_sceneManager;
    Ogre::Light *_light;
    Ogre::Entity *_ogreHead;
    Ogre::SceneNode *_ogreNode;
    Ogre::Camera *_camera;
};


#endif //OGREBM_GAMESTATE_HPP
