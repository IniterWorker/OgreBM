# include "Entities/Bomb.hpp"

Bomb::Bomb(Ogre::SceneManager *mgr, const Ogre::Vector2& pos, const Map& map, int power, Body* father)
{
  p_node = mgr->getRootSceneNode()->createChildSceneNode();
  std::ostringstream    os;

  os << "Bomb" << pos;
  p_entity_black = mgr->createEntity("Black" + os.str(), "bomb_black.mesh");
  p_entity_red = mgr->createEntity("Red" + os.str(), "bomb_red.mesh");
  p_node->setPosition(Ogre::Vector3(pos.x * map.getBlocDim().x, 0, pos.y * map.getBlocDim().z));
  p_node->setScale(Ogre::Vector3(2, 2, 2));
  p_node->attachObject(p_entity_black);
  p_pos = pos;
  p_cooldown = 1.5;
  p_mgr = mgr;
  p_power = power;
  p_father = father;
}

Bomb::~Bomb(void)
{
  try {
    p_node->detachObject(p_entity_black);
    p_node->detachObject(p_entity_black);
  } catch (std::exception) {}
  p_mgr->destroyEntity(p_entity_black);
  p_mgr->destroyEntity(p_entity_red);
  p_mgr->destroySceneNode(p_node);
}

bool  Bomb::update(float elapsedTime, Map& map)
{
  p_cooldown -= elapsedTime;
  if ((int)(p_cooldown * 10) % 2) {
    try {
      p_node->detachObject(p_entity_black);
      p_node->attachObject(p_entity_red);
    } catch (std::exception) {}
    p_node->setScale(Ogre::Vector3(2.5, 2.5, 2.5));
  } else {
    try {
      p_node->detachObject(p_entity_red);
      p_node->attachObject(p_entity_black);
    } catch (std::exception) {}
    p_node->setScale(Ogre::Vector3(2, 2, 2));
  }
  if (p_cooldown <= 0) {
    map.makeExplosion(p_pos, p_power);
    p_father->removeBomb();
    return (true);
  }
  return (false);
}
