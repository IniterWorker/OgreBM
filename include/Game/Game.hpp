//
//-----------------------------------------------------------------------------
//Filename:    Game.hpp
//-----------------------------------------------------------------------------
//
// Created by bonett_w on 7/3/17.
//-----------------------------------------------------------------------------
//

#ifndef OGREBM_GAME_HPP
#define OGREBM_GAME_HPP


#include <vector>
#include <Entities/Player.hpp>
#include "Map.hpp"
#include "Controller.hpp"

class Game {
protected:
    Ogre::SceneManager *_sceneManager;
    Ogre::RenderWindow *_renderWindow;
    Controller *_controller;
    std::vector<Player *> _vPlayers;
    Map *_map;
public:
    Game(Ogre::RenderWindow *renderWindow, Ogre::SceneManager *sceneManager);

    virtual ~Game();

    void update(Ogre::Real elapsedTime);

    Map *getMap();

    std::vector<Player *> &getPlayers();
};


#endif //OGREBM_GAME_HPP
