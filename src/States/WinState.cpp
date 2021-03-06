#include "OgreFramework.hpp"
#include "States/WinState.hpp"

WinState::WinState() : _isQuit(false), _time(0), _awaitingTime(2) {

}

void WinState::enter() {
    // Ogre::ResourceGroupManager::getSingleton().initialiseResourceGroup("General");
    OgreFramework::getSingletonPtr()->_log->logMessage("Entering WinState...");

    // SceneManager
    _sceneManager = OgreFramework::getSingletonPtr()->_root->createSceneManager(Ogre::ST_GENERIC, "WinSceneMgr");
    _sceneManager->setAmbientLight(Ogre::ColourValue(0.0f, 0.0f, 0.0f, 1.0f));
    _sceneManager->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_MODULATIVE);
    _sceneManager->addRenderQueueListener(OgreFramework::getSingletonPtr()->_overlaySystem);

    // TrayManager
    OgreFramework::getSingletonPtr()->_trayManager->destroyAllWidgets();
    OgreFramework::getSingletonPtr()->_trayManager->hideCursor();
    // OgreFramework::getSingletonPtr()->_trayManager->showFrameStats(OgreBites::TL_BOTTOMLEFT);
    // OgreFramework::getSingletonPtr()->_trayManager->createLabel(OgreBites::TL_TOP, "MenuLbl", "WinState", 250);

    // Scene
    createScene();
}

void WinState::createScene() {
    // Init Camera
    _camera = _sceneManager->createCamera("MainCamera");
    _camera->setAspectRatio(
            Ogre::Real(OgreFramework::getSingletonPtr()->_viewport->getActualWidth()) /
            Ogre::Real(OgreFramework::getSingletonPtr()->_viewport->getActualHeight()));
    _camera->setPosition(0, 0, 800);

    OgreFramework::getSingletonPtr()->_viewport->setCamera(_camera);

    OgreBites::DecorWidget *_logo = OgreFramework::getSingletonPtr()->_trayManager->createDecorWidget(OgreBites::TL_NONE, "Win/Logo", "OgreBMWin/WinLogo");
    OgreFramework::getSingletonPtr()->_trayManager->moveWidgetToTray(_logo, OgreBites::TL_CENTER, 0);
    OgreFramework::getSingletonPtr()->_trayManager->getBackdropLayer()->hide();
}

void WinState::exit() {

}

bool WinState::keyPressed(const OIS::KeyEvent &evt) {
  if (OgreFramework::getSingletonPtr()->_keyboard->isKeyDown(OIS::KC_ESCAPE)) {
    _isQuit = true;
    return true;
  }
  changeAppState(findByName("MenuState"));
  OgreFramework::getSingletonPtr()->keyPressed(evt);
  return true;
}

bool WinState::keyReleased(const OIS::KeyEvent &evt) {
    return false;
}

bool WinState::mouseMoved(const OIS::MouseEvent &evt) {
    if (OgreFramework::getSingletonPtr()->_trayManager->injectMouseMove(evt))
        return true;
}

bool WinState::mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id) {
    return false;
}

bool WinState::mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id) {
    return false;
}

void WinState::buttonHit(OgreBites::Button *button) {
    // SdkTrayListener::buttonHit(button);
}

void WinState::update(Ogre::Real timeSinceLastFrame) {
    _FrameEvent.timeSinceLastFrame = timeSinceLastFrame;
    OgreFramework::getSingletonPtr()->_trayManager->frameRenderingQueued(
            _FrameEvent);

    _time += timeSinceLastFrame;
    if (_time > _awaitingTime) {
        changeAppState(findByName("MenuState"));
    }

    if (_isQuit) {
        shutdown();
        return;
    }
}
