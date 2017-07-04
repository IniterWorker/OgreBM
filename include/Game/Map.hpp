#ifndef MAP_HPP
# define MAP_HPP

# include <vector>
# include <OgreVector2.h>
# include <OgreVector3.h>
# include <OgreSceneNode.h>
# include <OgreSceneManager.h>
# include <OgreEntity.h>
# include "OgreFramework.hpp"
# include <sstream>
# include <map>
# include <string>
# include <cstdlib>
# include <array>
# include "Entities/Bomb.hpp"

class Bomb;
class Body;

class   Map
{

public:

  enum class Bloc {
    EMPTY,
    WALL,
    EXPLOSION,
    BREAKABLE
  };

  typedef std::vector<std::vector<Bloc>>        Grid;

  Map(Ogre::SceneManager *mgr, size_t width = 21, size_t height = 21, float density = 0.8f);
  ~Map(void);

  void  makeExplosion(const Ogre::Vector2&, int power, const std::vector<Bomb*>&, const std::vector<Body*>& players);
  void  generateMap(size_t width, size_t height, float density);

  const Ogre::Vector3&  getMapDim(void) const;

  const Ogre::Vector3&  getBlocDim(void) const;

  const Grid&   accessGrid(void) const;

  Ogre::SceneNode *getNodeRoot();

  const Ogre::Vector3&  getStartEmplacement(int nb) const;
  const Ogre::Vector2&  getStartPos(int nb) const;
  void  update(float elapsedTime);

private:

  void  p_destroyCase(const Ogre::Vector2&, bool = false);
  void  p_createCase(const Ogre::Vector2&, Bloc, bool begin = true);
  void  p_clearMap(void);

  Grid  p_grid;

  std::vector<std::vector<Ogre::SceneNode*>>  p_drawMap;
  std::vector<std::vector<Ogre::SceneNode*>>  p_subPlane;

  std::vector<std::vector<float>>  p_explosionCooldown;

  std::array<Ogre::Vector3, 4>    p_startEmplacements;
  std::array<Ogre::Vector2, 4>    p_startPos;

  Ogre::SceneNode*    p_base;

  Ogre::SceneManager    *p_mgr;

  Ogre::Vector3 p_dim;
  Ogre::Vector3 p_blocDim;

  const float   p_explosionCooldownTime;

  static const std::map<Bloc, std::string>      p_blocMesh;

};


#endif /* MAP_HPP */
