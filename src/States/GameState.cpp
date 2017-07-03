//
//-----------------------------------------------------------------------------
//Filename:    GameState.cpp
//-----------------------------------------------------------------------------
//
// Created by bonett_w on 7/3/17.
//-----------------------------------------------------------------------------
//

#include "OgreFramework.hpp"
#include "States/GameState.hpp"

GameState::GameState() {

}

void GameState::enter() {
    OgreFramework::getSingletonPtr()->_log->logMessage("Entering GameState...");

    // SceneManager
    _sceneManager = OgreFramework::getSingletonPtr()->_root->createSceneManager(Ogre::ST_GENERIC, "GameSceneMgr");
    _sceneManager->setAmbientLight(Ogre::ColourValue(0.0f, 0.0f, 0.0f, 1.0f));
    _sceneManager->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_MODULATIVE);
    _sceneManager->addRenderQueueListener(OgreFramework::getSingletonPtr()->_overlaySystem);

    // TrayManager
    OgreFramework::getSingletonPtr()->_trayManager->destroyAllWidgets();
    OgreFramework::getSingletonPtr()->_trayManager->showFrameStats(OgreBites::TL_BOTTOMLEFT);
    OgreFramework::getSingletonPtr()->_trayManager->createLabel(OgreBites::TL_TOP, "MenuLbl", "GameState", 250);

    // Scene
    createScene();
}

void GameState::createScene() {
    // SkyBox
    _sceneManager->setSkyBox(true, "Examples/SpaceSkyBox", 300);

    // Light
    _light = _sceneManager->createLight("MainLight");
    _light->setDiffuseColour(Ogre::ColourValue(1.0, 1.0, 1.0));
    _light->setPosition(0, 200, 0);

    // Create an entity
    _ogreHead = _sceneManager->createEntity("ogrehead.mesh");
    _ogreNode = _sceneManager->getRootSceneNode()->createChildSceneNode("OgreNode");
    _ogreNode->attachObject(_ogreHead);
    _ogreNode->setPosition(0, 0, 0);

    // Init Camera
    _camera = _sceneManager->createCamera("MainCamera");
    _camera->setAspectRatio(
            Ogre::Real(OgreFramework::getSingletonPtr()->_viewport->getActualWidth()) /
            Ogre::Real(OgreFramework::getSingletonPtr()->_viewport->getActualHeight()));
    _camera->setPosition(0, 0, 300);

    OgreFramework::getSingletonPtr()->_viewport->setCamera(_camera);
}

void GameState::exit() {
    OgreFramework::getSingletonPtr()->_log->logMessage("Leaving GameState...");
}

bool GameState::keyPressed(const OIS::KeyEvent &evt) {
    if (OgreFramework::getSingletonPtr()->_keyboard->isKeyDown(OIS::KC_ESCAPE)) {
        _isQuit = true;
        return true;
    }

    OgreFramework::getSingletonPtr()->keyPressed(evt);
    return false;
}

bool GameState::keyReleased(const OIS::KeyEvent &evt) {
    return false;
}

bool GameState::mouseMoved(const OIS::MouseEvent &evt) {
    if (OgreFramework::getSingletonPtr()->_trayManager->injectMouseMove(evt))
        return true;
}

bool GameState::mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id) {
    return false;
}

bool GameState::mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id) {
    return false;
}

void GameState::buttonHit(OgreBites::Button *button) {
    // SdkTrayListener::buttonHit(button);
}

void GameState::update(Ogre::Real timeSinceLastFrame) {
    _FrameEvent.timeSinceLastFrame = timeSinceLastFrame;
    OgreFramework::getSingletonPtr()->_trayManager->frameRenderingQueued(_FrameEvent);

    if (_isQuit) {
        shutdown();
        return;
    }
}
