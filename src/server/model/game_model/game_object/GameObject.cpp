#include "GameObject.hpp"

namespace junk {
namespace server {
namespace model {

int TYPE_PLAYER = 1;
int TYPE_BULLET = 2;

MODEL_GAME_OBJECT_IMPL(GameObject, gameObject, GAME_OBJECT)

GameObject::GameObject() : lifetime(0), isRemoved(0)
{
}

GameObject::~GameObject()
{
}

GameObjectPatch GameObject::getGameObjectPatch()
{
  GameObjectPatch gameObjectPatch;

  gameObjectPatch.id = id;
  gameObjectPatch.destroyInfo.isDestructing = destroyInfo.isDestructing;
  if (destroyInfo.isDestructing)
  {
    gameObjectPatch.destroyInfo.destroyCountdown = destroyInfo.destroyCountdown;
  }

  return gameObjectPatch;
}

void GameObject::process()
{
    ++lifetime;
    if (destroyInfo.isDestructing)
    {
      destroyInfo.destroyCountdown = (destroyTime - std::chrono::high_resolution_clock::now()).count();
    }
}

}}} // namespace junk::server::model
