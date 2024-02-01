#pragma once

#include <vector>
#include <unordered_map>
#include "entity.hpp"


// EntityManager is a singleton responsible for managing all entities in the game.
// Following the ECS pattern, the Game class will be calling Systems that will
// operate on entities that are expected to be managed/maintained by the EntityManager.
class EntityManager {
public:
    EntityManager() = default;

    auto update() -> void;

    auto addEntity(EntityKind entityKind) -> RC<Entity>;

    auto getPlayer() -> OPT<RC<Entity>>;

    auto getEntities() -> const VEC<OPT<RC<Entity>>>&;

    auto getEntitiesBasedOnKind(EntityKind entityKind) -> const VEC<OPT<RC<Entity>>>&;

    auto addReservedPosition(Vec2f position) -> void;

    auto getReservedPositions() -> VEC<Vec2f>&;
private:
    VEC<OPT<RC<Entity>>>                                     entities = {};
    VEC<OPT<RC<Entity>>>                                     entitiesToAdd = {};
    // entitiesMap is a map of vectors of entities of the same kind, where the key is the entity kind.
    std::unordered_map<EntityKind, VEC<OPT<RC<Entity>>>>     entitiesMap = {};
    size_t                                                   totalEntities = 0;
    VEC<Vec2f>                                               reservedPositions;

    auto deleteDeadEntities(VEC<OPT<RC<Entity>>>& entityVec) -> void;
};