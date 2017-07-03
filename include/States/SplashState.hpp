//
//-----------------------------------------------------------------------------
//Filename:    SplashState.hpp
//-----------------------------------------------------------------------------
//
// Created by bonett_w on 7/3/17.
//-----------------------------------------------------------------------------
//

#ifndef OGREBM_SPLASHSTATE_HPP
#define OGREBM_SPLASHSTATE_HPP

#include <OGRE/OgreSceneManager.h>
#include <States/AppState.hpp>

class SplashState : public AppState {
public:
    SplashState();

    DECLARE_APPSTATE_CLASS(SplashState)

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
    bool _firstLoad;
    Ogre::SceneManager *_sceneManager;
    Ogre::Camera *_camera;
    Ogre::Real _time;
    Ogre::Real _awaitingTime;
    Ogre::TextureUnitState *tex;
};


#endif //OGREBM_SPLASHSTATE_HPP
