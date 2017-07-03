# include "Game/Map.hpp"

const std::map<Map::Bloc, std::string>      Map::p_blocMesh = {
  {Map::Bloc::WALL, "stone.mesh"},
  {Map::Bloc::BREAKABLE, "wood.mesh"}
};

Map::Map(Ogre::SceneManager *mgr, size_t width, size_t height, float density)
{
  p_mgr = mgr;

  Ogre::Entity *wall = p_mgr->createEntity("beginSample", p_blocMesh.at(Map::Bloc::WALL));
  p_base = p_mgr->getRootSceneNode()->createChildSceneNode();
  generateMap(width, height, density);
  p_dim.x = width * wall->getBoundingBox().getSize().x;
  p_dim.z = height * wall->getBoundingBox().getSize().z;
  p_dim.y = wall->getBoundingBox().getSize().y;
  p_mgr->destroyEntity("beginSample");
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
      p_destroyCase(Ogre::Vector2(j, i), true);
    }
  p_grid.clear();
  p_drawMap.clear();
  p_subPlane.clear();
}

const Map::Grid&     Map::accessGrid(void) const
{
  return (p_grid);
}

void    Map::p_destroyCase(const Ogre::Vector2& pos, bool end)
{
  p_grid[pos.y][pos.x] = Map::Bloc::EMPTY;
  std::ostringstream    os;

  os << "Bloc" << pos;

  try {
    p_drawMap[pos.y][pos.x]->detachObject(os.str());
    p_mgr->destroyEntity(p_mgr->getEntity(os.str()));
    if (end) {
      p_subPlane[pos.y][pos.x]->detachObject(os.str());
      p_mgr->destroyEntity(p_mgr->getEntity("Sub" + os.str()));
    }
  } catch (std::exception) {}
}

void    Map::p_createCase(const Ogre::Vector2& pos, Bloc blocType)
{
  std::ostringstream    os;

  os << "Bloc" << pos;

  p_subPlane[pos.y][pos.x]->attachObject(p_mgr->createEntity("Sub" + os.str(), p_blocMesh.at(Map::Bloc::WALL)));
  p_grid[pos.y][pos.x] = blocType;
  if (blocType != Map::Bloc::EMPTY)
    p_drawMap[pos.y][pos.x]->attachObject(p_mgr->createEntity(os.str(), p_blocMesh.at(blocType)));
}

void    Map::makeExplosion(const Ogre::Vector2& pos, int power)
{

  for (int i = 1 ; i <= power ; ++i)
    if (p_grid[pos.y + i][pos.x] == Map::Bloc::WALL)
      break;
    else if (p_grid[pos.y + i][pos.x] == Map::Bloc::BREAKABLE) {
      p_destroyCase(Ogre::Vector2(pos.x, pos.y + i));
      break;
    }
  for (int i = 1 ; i <= power ; ++i)
    if (p_grid[pos.y - i][pos.x] == Map::Bloc::WALL)
      break;
    else if (p_grid[pos.y - i][pos.x] == Map::Bloc::BREAKABLE) {
      p_destroyCase(Ogre::Vector2(pos.x, pos.y - i));
      break;
    }
  for (int i = 1 ; i <= power ; ++i)
    if (p_grid[pos.y][pos.x + i] == Map::Bloc::WALL)
      break;
    else if (p_grid[pos.y][pos.x + i] == Map::Bloc::BREAKABLE) {
      p_destroyCase(Ogre::Vector2(pos.x + i, pos.y));
      break;
    }
  for (int i = 1 ; i <= power ; ++i)
    if (p_grid[pos.y][pos.x - i] == Map::Bloc::WALL)
      break;
    else if (p_grid[pos.y][pos.x - i] == Map::Bloc::BREAKABLE) {
      p_destroyCase(Ogre::Vector2(pos.x - i, pos.y));
      break;
    }
}

const Ogre::Vector3&  Map::getMapDim(void) const
{
  return (p_dim);
}

void    Map::generateMap(size_t width, size_t height, float density)
{
  Ogre::Entity *wall = p_mgr->createEntity("sample", p_blocMesh.at(Map::Bloc::WALL));

  p_clearMap();
  p_grid.resize(height);
  p_drawMap.resize(height);
  p_subPlane.resize(height);
  for (size_t i = 0 ; i < height ; ++i) {
    p_grid[i].resize(width);
    p_drawMap[i].resize(width);
    p_subPlane[i].resize(width);
    for (size_t j = 0 ; j < width ; ++j) {
      p_grid[i][j] = Map::Bloc::EMPTY;
      p_drawMap[i][j] = p_base->createChildSceneNode();
      p_drawMap[i][j]->setPosition(j * wall->getBoundingBox().getSize().x, 0, i * wall->getBoundingBox().getSize().z);
      p_subPlane[i][j] = p_base->createChildSceneNode();
      p_subPlane[i][j]->setPosition(j * wall->getBoundingBox().getSize().x, -wall->getBoundingBox().getSize().y,
                                    i * wall->getBoundingBox().getSize().z);
      if (!i || !j || i == height - 1 || j == width - 1 ||
          (i % 2 == 0 && j % 2 == 0)) {
        p_grid[i][j] = Map::Bloc::WALL;
      } else if (rand() % 100 >= density * 100 ||
                 ((j <= 2 || j >= width - 3) &&
                  (i <= 2 || i >= height - 3))) {
        p_grid[i][j] = Map::Bloc::EMPTY;
      } else {
        p_grid[i][j] = Map::Bloc::BREAKABLE;
      }
      p_createCase(Ogre::Vector2(j, i), p_grid[i][j]);
    }
  }
  p_mgr->destroyEntity("sample");
}

Ogre::SceneNode *Map::getNodeRoot() {
    return p_base;
}
