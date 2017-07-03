//
//-----------------------------------------------------------------------------
//Filename:    AppStateManager.cpp
//-----------------------------------------------------------------------------
//
//This source file is part of the
//
// Created by bonett_w on 6/9/17.
//-----------------------------------------------------------------------------
//

#include <OgreFramework.hpp>
#include "States/AppStateManager.hpp"

AppStateManager::AppStateManager() {
    OgreFramework::getSingletonPtr()->_root->addFrameListener(this);
    _isShutdown = false;
}

AppStateManager::~AppStateManager() {
    state_info si;

    while (!_activeStateStack.empty()) {
        _activeStateStack.back()->exit();
        _activeStateStack.pop_back();
    }

    while (!_states.empty()) {
        si = _states.back();
        si.state->destroy();
        _states.pop_back();
    }
}

void AppStateManager::manageAppState(Ogre::String stateName, AppState *state) {
    try {
        state_info new_state_info;
        new_state_info.name = stateName;
        new_state_info.state = state;
        _states.push_back(new_state_info);
    }
    catch (std::exception &e) {
        delete state;
        throw Ogre::Exception(Ogre::Exception::ERR_INTERNAL_ERROR,
                              "Error while trying to manage a new AppState\n" +
                              Ogre::String(e.what()), "AppStateManager.cpp (39)");
    }
}

AppState *AppStateManager::findByName(Ogre::String stateName) {
    std::vector<state_info>::iterator itr;

    for (itr = _states.begin(); itr != _states.end(); itr++) {
        if (itr->name == stateName)
            return itr->state;
    }

    return 0;
}

void AppStateManager::start(AppState *state) {
    changeAppState(state);
    OgreFramework::getSingletonPtr()->_log->logMessage("Start Rendering");
    OgreFramework::getSingletonPtr()->_root->startRendering();
}

void AppStateManager::changeAppState(AppState *state) {
    if (!_activeStateStack.empty()) {
        _activeStateStack.back()->exit();
        _activeStateStack.pop_back();
    }

    _activeStateStack.push_back(state);
    init(state);
    _activeStateStack.back()->enter();
}

bool AppStateManager::pushAppState(AppState *state) {
    if (!_activeStateStack.empty()) {
        if (!_activeStateStack.back()->pause())
            return false;
    }

    _activeStateStack.push_back(state);
    init(state);
    _activeStateStack.back()->enter();

    return true;
}

void AppStateManager::popAppState() {
    if (!_activeStateStack.empty()) {
        _activeStateStack.back()->exit();
        _activeStateStack.pop_back();
    }

    if (!_activeStateStack.empty()) {
        init(_activeStateStack.back());
        _activeStateStack.back()->resume();
    } else
        shutdown();
}

void AppStateManager::popAllAndPushAppState(AppState *state) {
    while (!_activeStateStack.empty()) {
        _activeStateStack.back()->exit();
        _activeStateStack.pop_back();
    }

    pushAppState(state);
}

void AppStateManager::pauseAppState() {
    if (!_activeStateStack.empty()) {
        _activeStateStack.back()->pause();
    }

    if (_activeStateStack.size() > 2) {
        init(_activeStateStack.at(_activeStateStack.size() - 2));
        _activeStateStack.at(_activeStateStack.size() - 2)->resume();
    }
}

void AppStateManager::shutdown() {
    _isShutdown = true;
    OgreFramework::getSingletonPtr()->_log->logMessage("Shutdown Rendering");
    // OgreFramework::getSingletonPtr()->_root->removeFrameListener(this);
}

void AppStateManager::init(AppState *state) {
    OgreFramework::getSingletonPtr()->_keyboard->setEventCallback(state);
    OgreFramework::getSingletonPtr()->_mouse->setEventCallback(state);
    OgreFramework::getSingletonPtr()->_trayManager->setListener(state);

    OgreFramework::getSingletonPtr()->_window->resetStatistics();
}

bool AppStateManager::frameRenderingQueued(const Ogre::FrameEvent &evt) {
    if (OgreFramework::getSingletonPtr()->_window->isClosed())
        return false;

    OgreFramework::getSingletonPtr()->_keyboard->capture();
    OgreFramework::getSingletonPtr()->_mouse->capture();

    if (_isShutdown)
        return false;

    // if (evt.timeSinceLastEvent - 15.f < 0)
    //    usleep((int) (15.f - evt.timeSinceLastEvent) * 1000);

    if (_activeStateStack.size())
        _activeStateStack.back()->update(evt.timeSinceLastFrame);

    if (OgreFramework::getSingletonPtr()->_keyboard->isKeyDown(OIS::KC_ESCAPE))
        return false;

    return true;
}

bool AppStateManager::frameStarted(const Ogre::FrameEvent &evt) {
    return _activeStateStack.back()->frameStarted(evt);
}

bool AppStateManager::frameEnded(const Ogre::FrameEvent &evt) {
    return _activeStateStack.back()->frameEnded(evt);
}
