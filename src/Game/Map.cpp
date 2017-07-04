# include "Game/Map.hpp"

const std::map<Map::Bloc, std::string>      Map::p_blocMesh = {
  {Map::Bloc::WALL, "stone.mesh"},
  {Map::Bloc::BREAKABLE, "wood.mesh"},
  {Map::Bloc::EXPLOSION, "explosion.mesh"}
};

Map::Map(Ogre::SceneManager *mgr, size_t width, size_t height, float density):
  p_height(height),
  p_width(width),
  p_explosionCooldownTime(0.5)
{
  p_mgr = mgr;

  Ogre::Entity *wall = p_mgr->createEntity("beginSample", p_blocMesh.at(Map::Bloc::WALL));
  p_base = p_mgr->getRootSceneNode()->createChildSceneNode();
  p_startEmplacements[0] = Ogre::Vector3::ZERO;
  p_startEmplacements[1] = Ogre::Vector3::ZERO;
  p_startEmplacements[2] = Ogre::Vector3::ZERO;
  p_startEmplacements[3] = Ogre::Vector3::ZERO;
  generateMap(width, height, density);
  p_dim.x = width * wall->getBoundingBox().getSize().x;
  p_dim.z = height * wall->getBoundingBox().getSize().z;
  p_dim.y = wall->getBoundingBox().getSize().y;
  p_blocDim.x = wall->getBoundingBox().getSize().x;
  p_blocDim.z = wall->getBoundingBox().getSize().z;
  p_blocDim.y = wall->getBoundingBox().getSize().y;
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
  p_explosionCooldown.clear();
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

void    Map::p_createCase(const Ogre::Vector2& pos, Bloc blocType, bool begin)
{
  std::ostringstream    os;

  os << "Bloc" << pos;

  if (begin)
    p_subPlane[pos.y][pos.x]->attachObject(p_mgr->createEntity("Sub" + os.str(), p_blocMesh.at(Map::Bloc::WALL)));
  p_grid[pos.y][pos.x] = blocType;
  if (blocType != Map::Bloc::EMPTY)
    p_drawMap[pos.y][pos.x]->attachObject(p_mgr->createEntity(os.str(), p_blocMesh.at(blocType)));
}

void    Map::makeExplosion(const Ogre::Vector2& pos, int power, const std::vector<Bomb*>& bombs, const std::vector<Body*>& players)
{
  p_explosionCooldown[pos.y][pos.x] = p_explosionCooldownTime;
    for (auto j = players.begin() ; j != players.end() ; ++j) {
      if ((*j)->getPos() == Ogre::Vector2(pos.x, pos.y))
        (*j)->receiveExplosion();
    }
  for (int i = 1 ; i <= power ; ++i) {
    for (auto j = bombs.begin() ; j != bombs.end() ; ++j) {
      if ((*j)->getPos() == Ogre::Vector2(pos.x, pos.y + i))
        (*j)->mustExplode();
    }
    for (auto j = players.begin() ; j != players.end() ; ++j) {
      if ((*j)->getPos() == Ogre::Vector2(pos.x, pos.y + i))
        (*j)->receiveExplosion();
    }
    if (p_grid[pos.y + i][pos.x] == Map::Bloc::WALL)
      break;
    else if (p_grid[pos.y + i][pos.x] == Map::Bloc::BREAKABLE) {
      p_destroyCase(Ogre::Vector2(pos.x, pos.y + i));
      p_explosionCooldown[pos.y + i][pos.x] = p_explosionCooldownTime;
      break;
    }
    p_explosionCooldown[pos.y + i][pos.x] = p_explosionCooldownTime;
  }
  for (int i = 1 ; i <= power ; ++i) {
    for (auto j = bombs.begin() ; j != bombs.end() ; ++j) {
      if ((*j)->getPos() == Ogre::Vector2(pos.x, pos.y - i))
        (*j)->mustExplode();
    }
    for (auto j = players.begin() ; j != players.end() ; ++j) {
      if ((*j)->getPos() == Ogre::Vector2(pos.x, pos.y - i))
        (*j)->receiveExplosion();
    }
    if (p_grid[pos.y - i][pos.x] == Map::Bloc::WALL)
      break;
    else if (p_grid[pos.y - i][pos.x] == Map::Bloc::BREAKABLE) {
      p_destroyCase(Ogre::Vector2(pos.x, pos.y - i));
      p_explosionCooldown[pos.y - i][pos.x] = p_explosionCooldownTime;
      break;
    }
    p_explosionCooldown[pos.y - i][pos.x] = p_explosionCooldownTime;
  }
  for (int i = 1 ; i <= power ; ++i) {
    for (auto j = bombs.begin() ; j != bombs.end() ; ++j) {
      if ((*j)->getPos() == Ogre::Vector2(pos.x + i, pos.y))
        (*j)->mustExplode();
    }
    for (auto j = players.begin() ; j != players.end() ; ++j) {
      if ((*j)->getPos() == Ogre::Vector2(pos.x + i, pos.y))
        (*j)->receiveExplosion();
    }
    if (p_grid[pos.y][pos.x + i] == Map::Bloc::WALL)
      break;
    else if (p_grid[pos.y][pos.x + i] == Map::Bloc::BREAKABLE) {
      p_destroyCase(Ogre::Vector2(pos.x + i, pos.y));
      p_explosionCooldown[pos.y][pos.x + i] = p_explosionCooldownTime;
      break;
    }
    p_explosionCooldown[pos.y][pos.x + i] = p_explosionCooldownTime;
  }
  for (int i = 1 ; i <= power ; ++i) {
    for (auto j = bombs.begin() ; j != bombs.end() ; ++j) {
      if ((*j)->getPos() == Ogre::Vector2(pos.x - i, pos.y))
        (*j)->mustExplode();
    }
    for (auto j = players.begin() ; j != players.end() ; ++j) {
      if ((*j)->getPos() == Ogre::Vector2(pos.x - i, pos.y))
        (*j)->receiveExplosion();
    }
    if (p_grid[pos.y][pos.x - i] == Map::Bloc::WALL)
      break;
    else if (p_grid[pos.y][pos.x - i] == Map::Bloc::BREAKABLE) {
      p_destroyCase(Ogre::Vector2(pos.x - i, pos.y));
      p_explosionCooldown[pos.y][pos.x - i] = p_explosionCooldownTime;
      break;
    }
    p_explosionCooldown[pos.y][pos.x - i] = p_explosionCooldownTime;
  }
}

const Ogre::Vector3&  Map::getMapDim(void) const
{
  return (p_dim);
}

const Ogre::Vector3&  Map::getBlocDim(void) const
{
  return (p_blocDim);
}

void    Map::generateMap(size_t width, size_t height, float density)
{
  Ogre::Entity *wall = p_mgr->createEntity("sample", p_blocMesh.at(Map::Bloc::WALL));

  p_clearMap();
  p_grid.resize(height);
  p_drawMap.resize(height);
  p_subPlane.resize(height);
  p_explosionCooldown.resize(height);
  for (size_t i = 0 ; i < height ; ++i) {
    p_grid[i].resize(width);
    p_drawMap[i].resize(width);
    p_subPlane[i].resize(width);
    p_explosionCooldown[i].resize(width);
    for (size_t j = 0 ; j < width ; ++j) {
      p_grid[i][j] = Map::Bloc::EMPTY;
      p_explosionCooldown[i][j] = 0;
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
        if (j <= 2 && i <= 2 && p_startEmplacements[1] == Ogre::Vector3::ZERO) {
          p_startEmplacements[1] = p_drawMap[i][j]->getPosition();
          p_startPos[1] = Ogre::Vector2(j, i);
        } else if (j <= 2 && i >= height - 3 && p_startEmplacements[0] == Ogre::Vector3::ZERO) {
          p_startEmplacements[0] = p_drawMap[i][j]->getPosition();
          p_startPos[0] = Ogre::Vector2(j, i);
        } else if (j >= width - 3 && i <= 2 && p_startEmplacements[2] == Ogre::Vector3::ZERO) {
          p_startEmplacements[2] = p_drawMap[i][j]->getPosition();
          p_startPos[2] = Ogre::Vector2(j, i);
        } else if (j >= width - 3 && i >= height - 3 && p_startEmplacements[3] == Ogre::Vector3::ZERO) {
          p_startEmplacements[3] = p_drawMap[i][j]->getPosition();
          p_startPos[3] = Ogre::Vector2(j, i);
        }
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

const Ogre::Vector3&    Map::getStartEmplacement(int id) const
{
  return (p_startEmplacements[id]);
}

const Ogre::Vector2&    Map::getStartPos(int id) const
{
  return (p_startPos[id]);
}

void    Map::update(float elapsedTime)
{
  for (size_t i = 0 ; i < p_grid.size() ; ++i) {
    for (size_t j = 0 ; j < p_grid[0].size() ; ++j) {
      if (p_explosionCooldown[i][j] > 0)
        p_explosionCooldown[i][j] -= elapsedTime;
      if (p_grid[i][j] == Map::Bloc::EXPLOSION)
        p_destroyCase(Ogre::Vector2(j, i));
      if (p_explosionCooldown[i][j] > 0) {
        p_createCase(Ogre::Vector2(j, i), Map::Bloc::EXPLOSION, false);
        float scale = 2 / p_explosionCooldown[i][j];
        if (scale > 2.5)
          scale = 2.5;
        scale /= 2;
        p_drawMap[i][j]->setScale(Ogre::Vector3(scale, scale, scale));
      }
    }
  }
}

size_t Map::getHeight(void) const {
  return p_height;
}

size_t Map::getWidth(void) const {
  return p_width;
}
