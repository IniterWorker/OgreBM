# include <OgreFramework.hpp>
# include <States/OptState.hpp>

OptState::OptState() {
    _isQuit = false;
    _FrameEvent = Ogre::FrameEvent();
}

void OptState::enter() {
    OgreFramework::getSingletonPtr()
            ->_log->logMessage("Entering OptState...");

    _pSceneMgr = OgreFramework::getSingletonPtr()
            ->_root->createSceneManager(Ogre::ST_GENERIC, "OptSceneMgr");
    _pSceneMgr->setAmbientLight(Ogre::ColourValue(0.7f, 0.0f, 0.0f));

    _pSceneMgr->addRenderQueueListener(OgreFramework::getSingletonPtr()
                                               ->_overlaySystem);

    _pCamera = _pSceneMgr->createCamera("OptCam");
    _pCamera->setPosition(Ogre::Vector3(0, 25, -50));
    _pCamera->lookAt(Ogre::Vector3(0, 0, 0));
    _pCamera->setNearClipDistance(1);

    _pCamera->setAspectRatio(Ogre::Real(OgreFramework::getSingletonPtr()
                                                ->_viewport->getActualWidth()) /
                             Ogre::Real(OgreFramework::getSingletonPtr()
                                                ->_viewport->getActualHeight()));

    OgreFramework::getSingletonPtr()->_viewport->setCamera(_pCamera);

    OgreFramework::getSingletonPtr()->_trayManager->destroyAllWidgets();
    // OgreFramework::getSingletonPtr()->_trayManager->showFrameStats(OgreBites::TL_BOTTOMLEFT);
    // OgreFramework::getSingletonPtr()->_trayManager->showLogo(OgreBites::TL_BOTTOMRIGHT);
    OgreFramework::getSingletonPtr()->_trayManager->showCursor();
    OgreFramework::getSingletonPtr()->_trayManager->createButton(OgreBites::TL_CENTER,
                                                                 "MenuBtn", "Back to menu", 250);
    // OgreFramework::getSingletonPtr()->_trayManager->createLabel(OgreBites::TL_TOP,
    //                                                             "OptLbl", "Game Opt", 250);

    createScene();
}

void OptState::createScene() {

    OgreFramework::getSingletonPtr()
            ->_log->logMessage("CreateScene OptState...");
}

void OptState::exit() {
    OgreFramework::getSingletonPtr()->_log->logMessage("Leaving OptState...");

    _pSceneMgr->destroyCamera(_pCamera);
    if (_pSceneMgr)
        OgreFramework::getSingletonPtr()->_root->destroySceneManager(_pSceneMgr);

    OgreFramework::getSingletonPtr()->_trayManager->clearAllTrays();
    OgreFramework::getSingletonPtr()->_trayManager->destroyAllWidgets();
    OgreFramework::getSingletonPtr()->_trayManager->setListener(0);
}

bool OptState::keyPressed(const OIS::KeyEvent &keyEventRef) {
    if (OgreFramework::getSingletonPtr()->_keyboard->isKeyDown(OIS::KC_ESCAPE)) {
        _isQuit = true;
        return true;
    }

    OgreFramework::getSingletonPtr()->keyPressed(keyEventRef);
    return true;
}

bool OptState::keyReleased(const OIS::KeyEvent &keyEventRef) {
    OgreFramework::getSingletonPtr()->keyReleased(keyEventRef);
    return true;
}

bool OptState::mouseMoved(const OIS::MouseEvent &evt) {
    if (OgreFramework::getSingletonPtr()->_trayManager->injectMouseMove(evt))
        return true;
    return true;
}

bool OptState::mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id) {
    if (OgreFramework::getSingletonPtr()->_trayManager->injectMouseDown(evt, id))
        return true;
    return true;
}

bool OptState::mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id) {
    if (OgreFramework::getSingletonPtr()->_trayManager->injectMouseUp(evt, id))
        return true;
    return true;
}

void OptState::update(Ogre::Real timeSinceLastFrame) {
    _FrameEvent.timeSinceLastFrame = timeSinceLastFrame;
    OgreFramework::getSingletonPtr()->_trayManager->frameRenderingQueued(
            _FrameEvent);

    if (_isQuit) {
        shutdown();
        return;
    }
}

void OptState::buttonHit(OgreBites::Button *button) {
  if (button->getName() == "MenuBtn")
    changeAppState(findByName("MenuState"));
  //TODO: rewrite to the connection search
}
