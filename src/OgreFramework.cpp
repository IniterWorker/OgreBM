//
//-----------------------------------------------------------------------------
//Filename:    OgreFramework.cpp
//-----------------------------------------------------------------------------
//
//This source file is part of the
//
// Created by bonett_w on 6/8/17.
//-----------------------------------------------------------------------------
//

#include <Game/InputManager.hpp>
#include "OgreFramework.hpp"

template<> OgreFramework *Ogre::Singleton<OgreFramework>::msSingleton = 0;

OgreFramework::OgreFramework() {
    _root = 0;
    _window = 0;
    _viewport = 0;
    _log = 0;
    _timer = 0;
    _inputManager = 0;
    _keyboard = 0;
    _mouse = 0;
}

OgreFramework::~OgreFramework() {
    OgreFramework::getSingletonPtr()->_log->logMessage("Shutdown OGRE...");
    if (_inputManager)
        delete(_inputManager);
    if (_root)
        delete _root;
}


void OgreFramework::_initResourcesConfiguration() {
    Ogre::LogManager::getSingletonPtr()->logMessage("*** Initializing Resources ***");
    Ogre::String secName, typeName, archName;
    Ogre::ConfigFile cf;
    cf.load(_resourcesCfg);

    Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();
    while (seci.hasMoreElements()) {
        secName = seci.peekNextKey();
        Ogre::ConfigFile::SettingsMultiMap *settings = seci.getNext();
        Ogre::ConfigFile::SettingsMultiMap::iterator i;
        for (i = settings->begin(); i != settings->end(); ++i) {
            typeName = i->first;
            archName = i->second;
            Ogre::ResourceGroupManager::getSingleton().addResourceLocation(archName, typeName, secName);
        }
    }
    Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
    Ogre::ResourceGroupManager::getSingleton().initialiseResourceGroup("Splash");
    Ogre::ResourceGroupManager::getSingleton().initialiseResourceGroup("Lose");
    Ogre::ResourceGroupManager::getSingleton().initialiseResourceGroup("Essential");
    Ogre::LogManager::getSingletonPtr()->logMessage("*** Initializing Resources Completed ***");
}

bool OgreFramework::_configure() {
    if (!(_root->restoreConfig() || _root->showConfigDialog()))
        return false;
    return true;
}

bool
OgreFramework::initOgre(Ogre::String wndTitle, OIS::KeyListener *pKeyListener,
                        OIS::MouseListener *pMouseListener) {
#ifdef _DEBUG
    _resourcesCfg = "resources_d.cfg";
    _pluginsCfg = "plugins_d.cfg";
#else
    _resourcesCfg = "resources.cfg";
    _pluginsCfg = "plugins.cfg";
#endif

    Ogre::LogManager *logMgr = new Ogre::LogManager();

    _log = Ogre::LogManager::getSingleton().createLog("OgreLogfile.log", true, true, false);
    _log->setDebugOutputEnabled(true);

    _root = new Ogre::Root(_pluginsCfg);

    if (!_configure())
        return false;
    _window = _root->initialise(true, wndTitle);

    _viewport = _window->addViewport(0);
    _viewport->setBackgroundColour(Ogre::ColourValue::Black);

    _viewport->setCamera(0);

    _overlaySystem = new Ogre::OverlaySystem();

//    size_t hWnd = 0;
//    OIS::ParamList paramList;
//    _window->getCustomAttribute("WINDOW", &hWnd);
//
//    paramList.insert(OIS::ParamList::value_type("WINDOW", Ogre::StringConverter::toString(hWnd)));
//
//    Ogre::LogManager::getSingletonPtr()->logMessage("*** Initializing OIS ***");
//    _inputManager = OIS::InputManager::createInputSystem(paramList);
//
//    _keyboard = static_cast<OIS::Keyboard *>(_inputManager
//            ->createInputObject(OIS::OISKeyboard, true));
//    _mouse = static_cast<OIS::Mouse *>(_inputManager
//            ->createInputObject(OIS::OISMouse, true));
//
//    _mouse->getMouseState().height = _window->getHeight();
//    _mouse->getMouseState().width = _window->getWidth();
//
//    if (pKeyListener == 0)
//        _keyboard->setEventCallback(this);
//    else
//        _keyboard->setEventCallback(pKeyListener);
//
//    if (pMouseListener == 0)
//        _mouse->setEventCallback(this);
//    else
//        _mouse->setEventCallback(pMouseListener);

    _inputManager = new InputManager();
    InputManager::getSingletonPtr()->initialise(_window);

    InputManager::getSingletonPtr()->addKeyListener(this, "OgreFrameworkKey");
    InputManager::getSingletonPtr()->addMouseListener(this, "OgreFrameworkMouse");

    _initResourcesConfiguration();

    _keyboard = InputManager::getSingletonPtr()->getKeyboard();
    _mouse = InputManager::getSingletonPtr()->getMouse();

    _inputContext.mMouse = _mouse;
    _inputContext.mKeyboard = _keyboard;

    _trayManager = new OgreBites::SdkTrayManager("AOFTrayMgr", _window, _inputContext, 0);

    _timer = new Ogre::Timer();
    _timer->reset();

    _window->setActive(true);
    Ogre::LogManager::getSingletonPtr()->logMessage("*** Initializing Completed ***");
    return true;
}

void OgreFramework::updateOgre(double timeSinceLastFrame) {

}

bool OgreFramework::keyPressed(const OIS::KeyEvent &keyEventRef) {
    if (_keyboard->isKeyDown(OIS::KC_SYSRQ)) {
        _window->writeContentsToTimestampedFile("AOF_Screenshot_", ".jpg");
        return true;
    }

    if (_keyboard->isKeyDown(OIS::KC_O)) {
        if (_trayManager->isLogoVisible()) {
            _trayManager->hideFrameStats();
            _trayManager->hideLogo();
        } else {
            _trayManager->showFrameStats(OgreBites::TL_BOTTOMLEFT);
            _trayManager->showLogo(OgreBites::TL_BOTTOMRIGHT);
        }
    }

    return true;
}

bool OgreFramework::keyReleased(const OIS::KeyEvent &keyEventRef) {
    return true;
}

bool OgreFramework::mouseMoved(const OIS::MouseEvent &evt) {
    return true;
}

bool
OgreFramework::mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id) {
    return true;
}

bool
OgreFramework::mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id) {
    return true;
}
