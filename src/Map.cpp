# include "Map.hpp"

const std::map<Map::Bloc, std::string>      Map::p_blocMesh = {
  {Map::Bloc::WALL, "stone.mesh"},
  {Map::Bloc::BREAKABLE, "wood.mesh"}
};

Map::Map(Ogre::SceneManager *mgr, size_t width, size_t height, float density)
{
  p_mgr = mgr;
  p_base = p_mgr->getRootSceneNode()->createChildSceneNode();
  generateMap(width, height, density);
}

Map::~Map(void)
{
  p_clearMap();
  p_mgr->destroySceneNode(p_base);
}

void    Map::p_clearMap(void)
{
  p_base->removeAndDestroyAllChildren();
  for (auto i = 0 ; i != p_drawMap.size() ; ++i)
    for (auto j = 0 ; j != p_drawMap[0].size() ; ++j) {
      p_destroyCase(Ogre::Vector2(j, i));
    }
  p_grid.clear();
  p_drawMap.clear();
}

const Map::Grid&     Map::accessGrid(void) const
{
  return (p_grid);
}

void    Map::p_destroyCase(const Ogre::Vector2& pos)
{
  p_grid[pos.y][pos.x] = Map::Bloc::EMPTY;
  std::ostringstream    os;

  os << "Bloc" << pos;

  try {
    p_mgr->destroyEntity(p_mgr->getEntity(os.str()));
    p_drawMap[pos.y][pos.x]->detachObject(os.str());
  } catch (std::exception) {}
}

void    Map::p_createCase(const Ogre::Vector2& pos, Bloc blocType)
{
  if (blocType == Map::Bloc::EMPTY)
    return ;
  std::ostringstream    os;

  os << "Bloc" << pos;

  p_drawMap[pos.y][pos.x]->attachObject(p_mgr->createEntity(os.str(), p_blocMesh.at(blocType)));
  p_grid[pos.y][pos.x] = blocType;
}

void    Map::makeExplosion(const Ogre::Vector2& pos, int power)
{
  (void)pos;
  (void)power;
}

void    Map::generateMap(size_t width, size_t height, float density)
{
  Ogre::Entity *wall = p_mgr->createEntity("sample", p_blocMesh.at(Map::Bloc::WALL));

  p_clearMap();
  p_grid.resize(height);
  p_drawMap.resize(height);
  for (size_t i = 0 ; i < height ; ++i) {
    p_grid[i].resize(width);
    p_drawMap[i].resize(width);
    for (size_t j = 0 ; j < width ; ++j) {
      p_grid[i][j] = Map::Bloc::EMPTY;
      p_drawMap[i][j] = p_base->createChildSceneNode();
      p_drawMap[i][j]->setPosition(j * wall->getBoundingBox().getSize().x, 0, i * wall->getBoundingBox().getSize().z);
      if (!i || !j || i == height - 1 || j == width - 1 ||
          (i % 2 == 0 && j % 2 == 0)) {
        p_grid[i][j] = Map::Bloc::WALL;
      } else if (rand() % 100 >= density * 100) {
        p_grid[i][j] = Map::Bloc::EMPTY;
      } else {
        p_grid[i][j] = Map::Bloc::BREAKABLE;
      }
      p_createCase(Ogre::Vector2(j, i), p_grid[i][j]);
    }
  }
  p_mgr->destroyEntity("sample");
}
