#include "GameObjectFactory.hpp"

#include <iostream>

#include "unit/player/Player.hpp"

namespace junk {
namespace client {
namespace model {

#define MODEL_GAME_OBJECT_REG( _Name, _name, _NAME) \
static bool model ## _Name ## _creator_registred = \
  GameObjectFactory::registerCreator<_Name>(GameObjectType::_NAME);

std::unordered_map<int, std::function<GameObject* ()> > GameObjectFactory::gameObjectCreator;
Logger GameObjectFactory::logger("CLIENT_GAME_OBJECT_FACTORY", "client_model.log", true);

MODEL_GAME_OBJECT_REG(Player, player, PLAYER)

GameObjectFactory::GameObjectFactory()
{
  logger << "GameObjectFactory created";
}

GameObjectFactory::~GameObjectFactory()
{
  logger << "GameObjectFactory destructed";
}

GameObject* GameObjectFactory::create(const GameObjectType::type &gameObjectType)
{
  logger << "Creating new object of type " + std::to_string(gameObjectType);
  return gameObjectCreator[gameObjectType]();
}

}}} // namespace junk::client::model
