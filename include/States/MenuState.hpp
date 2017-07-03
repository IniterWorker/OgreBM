//
//-----------------------------------------------------------------------------
//Filename:    MenuState.hpp
//-----------------------------------------------------------------------------
//
//This source file is part of the
//
// Created by bonett_w on 6/9/17.
//-----------------------------------------------------------------------------
//

#ifndef INDIESTUDIO_MENUSTATE_HPP
#define INDIESTUDIO_MENUSTATE_HPP

#include <States/AppState.hpp>

class MenuState : public AppState {
public:
    MenuState();

    DECLARE_APPSTATE_CLASS(MenuState)

    void enter();

    void createScene();

    void exit();

    bool keyPressed(const OIS::KeyEvent &keyEventRef);

    bool keyReleased(const OIS::KeyEvent &keyEventRef);

    bool mouseMoved(const OIS::MouseEvent &evt);

    bool mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id);

    bool mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id);

    void buttonHit(OgreBites::Button *button);

    void update(Ogre::Real timeSinceLastFrame);

private:
    bool _isQuit;
};


#endif //INDIESTUDIO_MENUSTATE_HPP
