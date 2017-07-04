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

GameState::GameState()
{

}

void GameState::enter() {
    OgreFramework::getSingletonPtr()->_log->logMessage("Entering GameState...");

    // SceneManager
    _sceneManager = OgreFramework::getSingletonPtr()->_root->createSceneManager(Ogre::ST_GENERIC, "GameSceneMgr");
    _sceneManager->setAmbientLight(Ogre::ColourValue(1.0f, 1.0f, 1.0f, 1.0f));
    _sceneManager->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_MODULATIVE);
    _sceneManager->setShadowColour(Ogre::ColourValue(0.95, 0.95, 0.95, 0.1));
    _sceneManager->addRenderQueueListener(OgreFramework::getSingletonPtr()->_overlaySystem);

    // Init Game Data
    _game = new Game(nullptr, _sceneManager);

    // TrayManager
    OgreFramework::getSingletonPtr()->_trayManager->destroyAllWidgets();
    // OgreFramework::getSingletonPtr()->_trayManager->showFrameStats(OgreBites::TL_BOTTOMLEFT);
    // OgreFramework::getSingletonPtr()->_trayManager->createLabel(OgreBites::TL_TOP, "MenuLbl", "GameState", 250);


    // Scene
    createScene();
}

void GameState::createScene() {
    // Map
    Map *map = _game->getMap();

    _player = new Player(_sceneManager, "MyPlayer", 0);
    InputManager::getSingletonPtr()->addKeyListener(_player, "MyPlayerKeyboard");

    _game->addPlayer(_player);
    _game->addIA("Bot1", "./ia/basic_ia.lua");
    _game->addIA("Bot2", "./ia/basic_ia.lua");
    // _game->addIA("Bot2", "./ia/basic_ia.lua");
    // _game->addIA("Bot3", "./ia/basic_ia.lua");

    // SkyBox
    _sceneManager->setSkyBox(true, "Examples/SpaceSkyBox", 300);

    // Light
    _light = _sceneManager->createLight("MainLight");
    _light->setDiffuseColour(Ogre::ColourValue(1.0, 1.0, 1.0));

    // Init Camera
    _camera = _sceneManager->createCamera("MainCamera");
    _camera->setAspectRatio(
            Ogre::Real(OgreFramework::getSingletonPtr()->_viewport->getActualWidth()) /
            Ogre::Real(OgreFramework::getSingletonPtr()->_viewport->getActualHeight()));
    _camera->setPosition(map->getMapDim().x * 1.5f, map->getMapDim().y * 10, map->getMapDim().z / 2);
    _camera->setNearClipDistance(2);
    _camera->lookAt(map->getMapDim() / 2);
    Ogre::Vector3 vec = map->getMapDim();
    vec /= 2;
    vec.y += 100;
    _light->setPosition(vec);

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

    _game->update(timeSinceLastFrame);

    if (!_player->isAlive())
      changeAppState(findByName("LoseState"));

    if (_isQuit) {
        shutdown();
        return;
    }
}
