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

class   Map
{

public:

  enum class Bloc {
    EMPTY,
    WALL,
    BREAKABLE
  };

  typedef std::vector<std::vector<Bloc>>        Grid;

  Map(Ogre::SceneManager *mgr, size_t width = 21, size_t height = 21, float density = 0.5f);
  ~Map(void);

  void  makeExplosion(const Ogre::Vector2&, int power);
  void  generateMap(size_t width, size_t height, float density);

  const Ogre::Vector3&  getMapDim(void) const;

  const Grid&   accessGrid(void) const;

  Ogre::SceneNode *getNodeRoot();

private:

  void  p_destroyCase(const Ogre::Vector2&, bool = false);
  void  p_createCase(const Ogre::Vector2&, Bloc);
  void  p_clearMap(void);

  Grid  p_grid;

  std::vector<std::vector<Ogre::SceneNode*>>  p_drawMap;
  std::vector<std::vector<Ogre::SceneNode*>>  p_subPlane;

  Ogre::SceneNode*    p_base;

  Ogre::SceneManager    *p_mgr;

  Ogre::Vector3 p_dim;

  static const std::map<Bloc, std::string>      p_blocMesh;

};


#endif /* MAP_HPP */
