//
//-----------------------------------------------------------------------------
//Filename:    MenuState.cpp
//-----------------------------------------------------------------------------
//
//This source file is part of the
//
// Created by bonett_w on 6/9/17.
//-----------------------------------------------------------------------------
//

#include <OgreFramework.hpp>
#include <States/MenuState.hpp>

MenuState::MenuState() {
    _isQuit = false;
    _FrameEvent = Ogre::FrameEvent();
}

void MenuState::enter() {
    OgreFramework::getSingletonPtr()
            ->_log->logMessage("Entering MenuState...");

    _pSceneMgr = OgreFramework::getSingletonPtr()
            ->_root->createSceneManager(Ogre::ST_GENERIC, "MenuSceneMgr");
    _pSceneMgr->setAmbientLight(Ogre::ColourValue(0.7f, 0.0f, 0.0f));

    _pSceneMgr->addRenderQueueListener(OgreFramework::getSingletonPtr()
                                               ->_overlaySystem);

    _pCamera = _pSceneMgr->createCamera("MenuCam");
    _pCamera->setPosition(Ogre::Vector3(0, 25, -50));
    _pCamera->lookAt(Ogre::Vector3(0, 0, 0));
    _pCamera->setNearClipDistance(1);

    _pCamera->setAspectRatio(Ogre::Real(OgreFramework::getSingletonPtr()
                                                ->_viewport->getActualWidth()) /
                             Ogre::Real(OgreFramework::getSingletonPtr()
                                                ->_viewport->getActualHeight()));

    OgreFramework::getSingletonPtr()->_viewport->setCamera(_pCamera);

    OgreFramework::getSingletonPtr()->_trayManager->destroyAllWidgets();
    OgreFramework::getSingletonPtr()->_trayManager->showFrameStats(OgreBites::TL_BOTTOMLEFT);
    OgreFramework::getSingletonPtr()->_trayManager->showLogo(OgreBites::TL_BOTTOMRIGHT);
    OgreFramework::getSingletonPtr()->_trayManager->showCursor();
    OgreFramework::getSingletonPtr()->_trayManager->createButton(OgreBites::TL_CENTER,
                                                                 "EnterBtn", "Enter GameState", 250);
    OgreFramework::getSingletonPtr()->_trayManager->createButton(OgreBites::TL_CENTER,
                                                                 "ExitBtn", "Exit AdvancedOgreFramework", 250);
    OgreFramework::getSingletonPtr()->_trayManager->createLabel(OgreBites::TL_TOP,
                                                                "MenuLbl", "Menu mode", 250);

    createScene();
}

void MenuState::createScene() {

    OgreFramework::getSingletonPtr()
            ->_log->logMessage("CreateScene MenuState...");
}

void MenuState::exit() {
    OgreFramework::getSingletonPtr()->_log->logMessage("Leaving MenuState...");

    _pSceneMgr->destroyCamera(_pCamera);
    if (_pSceneMgr)
        OgreFramework::getSingletonPtr()->_root->destroySceneManager(_pSceneMgr);

    OgreFramework::getSingletonPtr()->_trayManager->clearAllTrays();
    OgreFramework::getSingletonPtr()->_trayManager->destroyAllWidgets();
    OgreFramework::getSingletonPtr()->_trayManager->setListener(0);
}

bool MenuState::keyPressed(const OIS::KeyEvent &keyEventRef) {
    if (OgreFramework::getSingletonPtr()->_keyboard->isKeyDown(OIS::KC_ESCAPE)) {
        _isQuit = true;
        return true;
    }

    OgreFramework::getSingletonPtr()->keyPressed(keyEventRef);
    return true;
}

bool MenuState::keyReleased(const OIS::KeyEvent &keyEventRef) {
    OgreFramework::getSingletonPtr()->keyReleased(keyEventRef);
    return true;
}

bool MenuState::mouseMoved(const OIS::MouseEvent &evt) {
    if (OgreFramework::getSingletonPtr()->_trayManager->injectMouseMove(evt))
        return true;
    return true;
}

bool MenuState::mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id) {
    if (OgreFramework::getSingletonPtr()->_trayManager->injectMouseDown(evt, id))
        return true;
    return true;
}

bool MenuState::mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id) {
    if (OgreFramework::getSingletonPtr()->_trayManager->injectMouseUp(evt, id))
        return true;
    return true;
}

void MenuState::update(Ogre::Real timeSinceLastFrame) {
    _FrameEvent.timeSinceLastFrame = timeSinceLastFrame;
    OgreFramework::getSingletonPtr()->_trayManager->frameRenderingQueued(
            _FrameEvent);

    if (_isQuit) {
        shutdown();
        return;
    }
}

void MenuState::buttonHit(OgreBites::Button *button) {
    if (button->getName() == "ExitBtn")
        _isQuit = true;
    else if (button->getName() == "EnterBtn")
        changeAppState(findByName("GameState"));
    //TODO: rewrite to the connection search
}