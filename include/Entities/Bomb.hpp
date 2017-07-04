#ifndef BOMB_HPP
# define BOMB_HPP

# include <OgreVector2.h>
# include <OgreEntity.h>
# include <OgreSceneManager.h>
# include <OgreSceneNode.h>
# include "Game/Map.hpp"
# include <sstream>
# include "Entities/Body.hpp"

class Body;

class   Bomb
{

public:

  Bomb(Ogre::SceneManager *mgr, const Ogre::Vector2& pos, const Map& map, int power, Body *father);
  ~Bomb(void);

  bool  update(float elapsedTime, Map& map);

private:

  Body                  *p_father;
  Ogre::SceneManager    *p_mgr;
  Ogre::SceneNode       *p_node;
  Ogre::Entity  *p_entity_black;
  Ogre::Entity  *p_entity_red;
  float         p_cooldown;
  Ogre::Vector2 p_pos;
  int           p_power;

};


#endif /* BOMB_HPP */
