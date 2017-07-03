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
#include <Entities/Body.hpp>
#include <Entities/Player.hpp>
#include "Map.hpp"

class Game {
protected:
    Ogre::SceneManager *_sceneManager;
    Ogre::RenderWindow *_renderWindow;
    std::vector<Body *> _vPlayers;
    Map *_map;
public:
    Game(Ogre::RenderWindow *renderWindow, Ogre::SceneManager *sceneManager);

    virtual ~Game();

    void update(Ogre::Real elapsedTime);

    Map *getMap();

    void addPlayer(Player *player);

    std::vector<Body *> &getPlayers();
};


#endif //OGREBM_GAME_HPP
