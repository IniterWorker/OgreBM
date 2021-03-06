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
# include "Entities/Bomb.hpp"

class Game {
protected:
    Ogre::SceneManager *_sceneManager;
    Ogre::RenderWindow *_renderWindow;
    std::vector<Body *> _vPlayers;
    std::vector<Bomb *> _vBombs;
    Map *_map;
  float _mvCooldown;
public:
    Game(Ogre::RenderWindow *renderWindow, Ogre::SceneManager *sceneManager);

    virtual ~Game();

    void update(Ogre::Real elapsedTime);

    Map *getMap();

    void addPlayer(Player *player);

    void addIA(const std::string &name, const std::string &scriptPath);

    std::vector<Body *> &getPlayers();
};


#endif //OGREBM_GAME_HPP
