//
//-----------------------------------------------------------------------------
//Filename:    AppState.hpp
//-----------------------------------------------------------------------------
//
//This source file is part of the
//
// Created by bonett_w on 6/9/17.
//-----------------------------------------------------------------------------
//

#ifndef INDIESTUDIO_APPSTATE_HPP
#define INDIESTUDIO_APPSTATE_HPP

#include <OgreString.h>
#include <OISKeyboard.h>
#include <SdkTrays.h>

class AppState;

class AppStateListener {
public:
    AppStateListener() {};

    virtual ~AppStateListener() {};

    virtual void manageAppState(Ogre::String stateName, AppState *state) = 0;

    virtual AppState *findByName(Ogre::String stateName) = 0;

    virtual void changeAppState(AppState *state) = 0;

    virtual bool pushAppState(AppState *state) = 0;

    virtual void popAppState() = 0;

    virtual void pauseAppState() = 0;

    virtual void shutdown() = 0;

    virtual void popAllAndPushAppState(AppState *state) = 0;
};

class AppState
        : public Ogre::WindowEventListener,
          public Ogre::FrameListener,
          public OIS::KeyListener,
          public OIS::MouseListener,
          public OgreBites::SdkTrayListener {
public:
    static void create(AppStateListener *parent, const Ogre::String name) {};

    void destroy() { delete this; }

    virtual void enter() = 0;

    virtual void exit() = 0;

    virtual bool pause();

    virtual void resume();

    virtual void update(Ogre::Real timeSinceLastFrame) = 0;

protected:
    AppState() {};

    AppState *findByName(Ogre::String stateName);

    void changeAppState(AppState *state);

    bool pushAppState(AppState *state);

    void popAppState();

    void shutdown();

    void popAllAndPushAppState(AppState *state);

    AppStateListener *_pParent;

    Ogre::Camera *_pCamera;
    Ogre::SceneManager *_pSceneMgr;
    Ogre::FrameEvent _FrameEvent;
};


#define DECLARE_APPSTATE_CLASS(T)                                        \
static void create(AppStateListener* parent, const Ogre::String name)        \
{                                                                        \
        T* myAppState = new T();                                        \
        myAppState->_pParent = parent;                                        \
        parent->manageAppState(name, myAppState);                        \
}


#endif //INDIESTUDIO_APPSTATE_HPP
