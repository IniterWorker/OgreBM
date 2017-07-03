//
//-----------------------------------------------------------------------------
//Filename:    SplashState.cpp
//-----------------------------------------------------------------------------
//
// Created by bonett_w on 7/3/17.
//-----------------------------------------------------------------------------
//

#include "OgreFramework.hpp"
#include "States/SplashState.hpp"

SplashState::SplashState() : _firstLoad(false), _isQuit(false), _time(0), _awaitingTime(5) {

}

void SplashState::enter() {
    // Ogre::ResourceGroupManager::getSingleton().initialiseResourceGroup("General");
    OgreFramework::getSingletonPtr()->_log->logMessage("Entering SplashState...");

    // SceneManager
    _sceneManager = OgreFramework::getSingletonPtr()->_root->createSceneManager(Ogre::ST_GENERIC, "SplashSceneMgr");
    _sceneManager->setAmbientLight(Ogre::ColourValue(0.0f, 0.0f, 0.0f, 1.0f));
    _sceneManager->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_MODULATIVE);
    _sceneManager->addRenderQueueListener(OgreFramework::getSingletonPtr()->_overlaySystem);

    // TrayManager
    OgreFramework::getSingletonPtr()->_trayManager->destroyAllWidgets();
    OgreFramework::getSingletonPtr()->_trayManager->showFrameStats(OgreBites::TL_BOTTOMLEFT);
    OgreFramework::getSingletonPtr()->_trayManager->createLabel(OgreBites::TL_TOP, "MenuLbl", "SplashState", 250);

    // Scene
    createScene();
}

void SplashState::createScene() {
    // Init Camera
    _camera = _sceneManager->createCamera("MainCamera");
    _camera->setAspectRatio(
            Ogre::Real(OgreFramework::getSingletonPtr()->_viewport->getActualWidth()) /
            Ogre::Real(OgreFramework::getSingletonPtr()->_viewport->getActualHeight()));
    _camera->setPosition(0, 0, 300);

    OgreFramework::getSingletonPtr()->_viewport->setCamera(_camera);
}

void SplashState::exit() {

}

bool SplashState::keyPressed(const OIS::KeyEvent &evt) {
    if (OgreFramework::getSingletonPtr()->_keyboard->isKeyDown(OIS::KC_ESCAPE)) {
        _isQuit = true;
        return true;
    }

    OgreFramework::getSingletonPtr()->keyPressed(evt);
}

bool SplashState::keyReleased(const OIS::KeyEvent &evt) {
    return false;
}

bool SplashState::mouseMoved(const OIS::MouseEvent &evt) {
    if (OgreFramework::getSingletonPtr()->_trayManager->injectMouseMove(evt))
        return true;
}

bool SplashState::mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id) {
    return false;
}

bool SplashState::mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id) {
    return false;
}

void SplashState::buttonHit(OgreBites::Button *button) {
    // SdkTrayListener::buttonHit(button);
}

void SplashState::update(Ogre::Real timeSinceLastFrame) {
    _FrameEvent.timeSinceLastFrame = timeSinceLastFrame;
    OgreFramework::getSingletonPtr()->_trayManager->frameRenderingQueued(
            _FrameEvent);

    if (!_firstLoad) {
        _firstLoad = true;
        Ogre::ResourceGroupManager::getSingleton().initialiseResourceGroup("General");
    }

    _time += timeSinceLastFrame;
    if (_time > _awaitingTime) {
        changeAppState(findByName("MenuState"));
    }

    if (_isQuit) {
        shutdown();
        return;
    }
}
