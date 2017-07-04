//
//-----------------------------------------------------------------------------
//Filename:    Player.hpp
//-----------------------------------------------------------------------------
//
// Created by bonett_w on 7/3/17.
//-----------------------------------------------------------------------------
//

#ifndef OGREBM_PLAYER_HPP
#define OGREBM_PLAYER_HPP


#include <OgreSceneManager.h>
#include "Body.hpp"

class Player : public Body, public OIS::KeyListener {
public:

    Player(Ogre::SceneManager *sceneManager, const std::string &name);

    bool keyPressed(const OIS::KeyEvent &arg) override;

    bool keyReleased(const OIS::KeyEvent &arg) override;

private:
    ActionPlayer _lastKey;
};

#endif //OGREBM_PLAYER_HPP
