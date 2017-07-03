//
//-----------------------------------------------------------------------------
//Filename:    OgreFramework.hpp
//-----------------------------------------------------------------------------
//
//This source file is part of the
//
// Created by bonett_w on 6/8/17.
//-----------------------------------------------------------------------------
//

#ifndef INDIESTUDIO_OGREFRAMEWORK_HPP
#define INDIESTUDIO_OGREFRAMEWORK_HPP

#include <Game/InputManager.hpp>

#include <OgreCamera.h>
#include <OgreEntity.h>
#include <OgreLogManager.h>
#include <OgreOverlay.h>
#include <OgreOverlayElement.h>
#include <OgreOverlayManager.h>
#include <OgreRoot.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include <OgreConfigFile.h>

#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>

#include <SdkTrays.h>

class OgreFramework :
        public Ogre::Singleton<OgreFramework>,
        OIS::KeyListener,
        OIS::MouseListener {
private:
    Ogre::String _resourcesCfg;
    Ogre::String _pluginsCfg;
public:
    Ogre::Root *_root;
    Ogre::RenderWindow *_window;
    Ogre::Viewport *_viewport;
    Ogre::Log *_log;
    Ogre::Timer *_timer;
    Ogre::OverlaySystem *_overlaySystem;

    InputManager *_inputManager;
    OIS::Keyboard *_keyboard;
    OIS::Mouse *_mouse;
    OgreBites::InputContext _inputContext;
    OgreBites::SdkTrayManager *_trayManager;

public:
    OgreFramework();

    ~OgreFramework();

    bool initOgre(Ogre::String wndTitle, OIS::KeyListener *pKeyListener = 0,
                  OIS::MouseListener *pMouseListener = 0);

    void updateOgre(double timeSinceLastFrame);

    bool keyPressed(const OIS::KeyEvent &keyEventRef);

    bool keyReleased(const OIS::KeyEvent &keyEventRef);

    bool mouseMoved(const OIS::MouseEvent &evt);

    bool mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id);

    bool mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id);

private:
    OgreFramework(const OgreFramework &);

    OgreFramework &operator=(const OgreFramework &);

private:
    void _initResourcesConfiguration(void);

    bool _configure(void);
};


#endif //INDIESTUDIO_OGREFRAMEWORK_HPP
