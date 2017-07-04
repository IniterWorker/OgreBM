//
//-----------------------------------------------------------------------------
//Filename:    Application.cpp
//-----------------------------------------------------------------------------
//
//This source file is part of the
//
// Created by bonett_w on 6/9/17.
//-----------------------------------------------------------------------------
//


#include <States/SplashState.hpp>
#include "States/GameState.hpp"
#include "States/OptState.hpp"
#include "States/MenuState.hpp"
#include "States/AppStateManager.hpp"
#include "Application.hpp"

Application::Application(void) : _appStateManager(0) {

}

Application::~Application(void) {
    if (_appStateManager)
        delete _appStateManager;
    delete OgreFramework::getSingletonPtr();
}

void Application::start() {
    _ogreFramework = new OgreFramework();
    if (!OgreFramework::getSingletonPtr()->initOgre("Runaway", 0, 0))
        return;

    OgreFramework::getSingletonPtr()->_log->logMessage("Application initialized!");

    _appStateManager = new AppStateManager();
    OgreFramework::getSingletonPtr()->_log->logMessage("Application Load State!");
    MenuState::create(_appStateManager, "MenuState");
    GameState::create(_appStateManager, "GameState");
    SplashState::create(_appStateManager, "SplashState");
    OptState::create(_appStateManager, "OptState");

    OgreFramework::getSingletonPtr()->_log->logMessage("State initialized!");
    _appStateManager->start(_appStateManager->findByName("SplashState"));
}
