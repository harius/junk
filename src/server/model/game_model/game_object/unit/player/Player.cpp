#include "Player.hpp"

namespace junk {
namespace server {
namespace model {

Player::Player()
{
}

Player::~Player()
{
}

Patch Player::getPatch()
{
  Patch patch;
  patch.playerPatch = getPlayerPatch();
  return patch;
}

PlayerPatch Player::getPlayerPatch()
{
  Patch playerPatch;
  playerPatch.unitPatch = getUnitPatch();

  /*
    Set fields here
  */

  return playerPatch;
}

}}} // namespace junk::server::model
