//
//-----------------------------------------------------------------------------
//Filename:    Application.hpp
//-----------------------------------------------------------------------------
//
//This source file is part of the
//
// Created by bonett_w on 6/9/17.
//-----------------------------------------------------------------------------
//

#ifndef INDIESTUDIO_APPLICATION_HPP
#define INDIESTUDIO_APPLICATION_HPP

#include <States/AppStateManager.hpp>
#include <OgreFramework.hpp>

class Application {
public:
    Application(void);

    virtual ~Application(void);

    void start();

private:
    AppStateManager *_appStateManager;
    OgreFramework *_ogreFramework;
};


#endif //INDIESTUDIO_APPLICATION_HPP
