#pragma once

#include "server/model/game_model/game_object/unit/Unit.hpp"
#include "common/game_object/unit/bullet/Bullet.hpp"

namespace junk {
namespace server {
namespace model {

class Bullet : public virtual Unit, public virtual junk::common::Bullet
{
public:
    Bullet();
    virtual ~Bullet();

    virtual Patch getPatch();
    BulletPatch getBulletPatch();
    virtual void process();

}; // Bullet

}}} // namespace junk::server::model