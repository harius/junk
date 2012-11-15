#include "ServerGameModel.hpp"
#include "common/utils/Convert.hpp"
#include <functional>
#include <math.h>

namespace junk {
namespace server {
namespace model {

ServerGameModel::ServerGameModel()
: logger("SERVER_GAME_MODEL", "server_model.log", true), isRunning(false)
{
  b2AABB aabb;
  aabb.lowerBound.Set(-1000, -1000);
  aabb.upperBound.Set(1000, 1000);
  world = new b2World(aabb, b2Vec2(0, 0), true);
  logger << "ServerGameModel created";
  firstFreeId = 0;
}

ServerGameModel::~ServerGameModel()
{
  logger << "ServerGameModel destroyed";
  delete world;
}

void ServerGameModel::start()
{
  isRunning = true;
  gameLoopTimer.restart();
  gameLoopThread = std::thread(std::ref(*this));

  logger << "Game model started";
}

void ServerGameModel::stop()
{
  gameChangesMutex.lock();
  isRunning = false;
  gameChangesMutex.unlock();

  gameLoopThread.join();

  logger << "Game model stopped";
}

int32_t ServerGameModel::addPlayer(Player* player)
{
  gameChangesMutex.lock();

  logger << "Adding a player...";

  int32_t newPlayerId = firstFreeId++;

  logger << std::string("New player ID = ") + std::to_string(newPlayerId);

  player->id = newPlayerId;

  gameObjects.insert(std::make_pair(newPlayerId,
                    std::unique_ptr<GameObject> (player)));

  b2BodyDef bodyDef;
  bodyDef.position.Set(0, 0);
  b2Body* body = world->CreateBody(&bodyDef);
  b2CircleDef shapeDef;
  shapeDef.radius = 1;
  shapeDef.density = 40;
  body->CreateShape(&shapeDef);
  body->SetMassFromShapes();

  player->body = body;

  logger << "Player added";

  gameChangesMutex.unlock();

  return newPlayerId;
}

void ServerGameModel::removePlayer(int32_t playerId)
{
  gameChangesMutex.lock();

  logger << std::string("Removing a player with ID = ") + std::to_string(playerId);

  if (gameObjects.find(playerId) == gameObjects.end())
  {
    logger << std::string("There is no such player, id = ") + std::to_string(playerId);
  }
  else
  {
    gameObjects.erase(playerId);
    logger << "Player removed";
  }

  gameChangesMutex.unlock();
}

void ServerGameModel::makeAction(const Action& action)
{
  gameChangesMutex.lock();

  // I think we should check it in ServerModel, not here
  if (gameObjects.find(action.playerId) == gameObjects.end())
  {
    logger << "There is no such player with id " + std::to_string(action.playerId);
    return;
  }
  Player* player = dynamic_cast<Player*> (gameObjects[action.playerId].get());

  switch (action.actionType)
  {
    case ActionType::MOVE:
      move(player, action.moveAction);
      break;

    case ActionType::ROTATE:
      rotate(player, action.rotateAction);
      break;

    case ActionType::FIRE:
      fire(player, action.fireAction);
      break;
  }

  gameChangesMutex.unlock();
}

void ServerGameModel::move(Player* player, const MoveAction& moveAction)
{
  logger << "Move invoked";
  b2Vec2 force(moveAction.direction.x, moveAction.direction.y);
  player->force = force;
  /*logger << moveAction.direction.x;

  static const float speed = 25.0; // will be deleted

  sf::Vector2f direction = common::to_SFML_Vector2f(moveAction.direction);
  double length = sqrt(direction.x * direction.x + direction.y * direction.y);

  if (length < 1e-4)
    return;

  direction.x /= length;
  direction.y /= length;
  direction.x *= speed;
  direction.y *= speed;

  logger << player->position.x;
  logger << player->position.y;

  player->position += direction;*/
}

void ServerGameModel::rotate(Player* player, const RotateAction& rotateAction)
{
  //player->setRotation(rotation);
}

void ServerGameModel::fire(Player* player, const FireAction& fireAction)
{
}

GameChanges ServerGameModel::getChanges(int32_t id)
{
  GameChanges gameChanges;
  for (const auto& gameObject : gameObjects)
  {
    gameChanges.patches.push_back(gameObject.second->getPatch());
  }
  return gameChanges;
}

void ServerGameModel::operator()()
{
  while (true)
  {
    gameChangesMutex.lock();

    if (!isRunning)
    {
      gameChangesMutex.unlock();
      break;
    }
    world->Step(1.0/60, 4);
    for (auto& go : gameObjects) {
      //#kocTbl^U!
      Player* kost = dynamic_cast<Player*>(go.second.get());
      kost->body->ApplyForce(kost->force, kost->body->GetWorldCenter());
      b2Vec2 pos = kost->body->GetWorldCenter();
      kost->position.x = pos.x;
      kost->position.y = pos.y;
    }

    gameChangesMutex.unlock();
  }

  return;
}

}}} // namespace junk::server::model
