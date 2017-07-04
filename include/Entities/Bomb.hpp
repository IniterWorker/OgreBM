#ifndef BOMB_HPP
# define BOMB_HPP

# include <OgreVector2.h>
# include <OgreEntity.h>
# include <OgreSceneManager.h>
# include <OgreSceneNode.h>
# include "Game/Map.hpp"
# include <sstream>
# include <vector>
# include "Entities/Body.hpp"

class Body;
class Map;

class   Bomb
{

public:

  Bomb(Ogre::SceneManager *mgr, const Ogre::Vector2& pos, const Map& map, int power, Body *father);
  ~Bomb(void);

  bool  update(float elapsedTime, Map& map, const std::vector<Bomb*>& bombs, const std::vector<Body*>& players);

  const Ogre::Vector2&  getPos(void) const;

  void  mustExplode(void);

private:

  Body                  *p_father;
  Ogre::SceneManager    *p_mgr;
  Ogre::SceneNode       *p_node;
  Ogre::Entity  *p_entity_black;
  Ogre::Entity  *p_entity_red;
  float         p_cooldown;
  Ogre::Vector2 p_pos;
  int           p_power;
  bool          p_mustExplode;

};


#endif /* BOMB_HPP */
