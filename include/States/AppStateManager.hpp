//
//-----------------------------------------------------------------------------
//Filename:    AppStateManager.hpp
//-----------------------------------------------------------------------------
//
//This source file is part of the
//
// Created by bonett_w on 6/9/17.
//-----------------------------------------------------------------------------
//

#ifndef INDIESTUDIO_APPSTATEMANAGER_HPP
#define INDIESTUDIO_APPSTATEMANAGER_HPP


#include "AppState.hpp"

class AppStateManager :
        public AppStateListener,
        public Ogre::FrameListener {
public:
    typedef struct {
        Ogre::String name;
        AppState *state;
    } state_info;

    AppStateManager();

    ~AppStateManager();

    void manageAppState(Ogre::String stateName, AppState *state);

    AppState *findByName(Ogre::String stateName);

    void start(AppState *state);

    void changeAppState(AppState *state);

    bool pushAppState(AppState *state);

    void popAppState();

    void pauseAppState();

    void shutdown();

    void popAllAndPushAppState(AppState *state);

    bool frameRenderingQueued(const Ogre::FrameEvent &evt) override;

    bool frameStarted(const Ogre::FrameEvent &evt) override;

    bool frameEnded(const Ogre::FrameEvent &evt) override;

protected:
    void init(AppState *state);

    std::vector<AppState *> _activeStateStack;
    std::vector<state_info> _states;
    bool _isShutdown;
};

#endif //INDIESTUDIO_APPSTATEMANAGER_HPP
