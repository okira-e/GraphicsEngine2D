#include <vector>

#include "entityManager.hpp"
#include "utils.hpp"

auto EntityManager::update() -> void {
    //
    // Add new entities.
    //
    for (const auto& entity : this->entitiesToAdd) {
        this->entities.push_back(entity);
    }
    this->entitiesToAdd.clear();

    //
    // Delete dead entities.
    //
    this->deleteDeadEntities(this->entities);

    // Remove dead entities from entitiesMap.
    for (auto& [entityKind, entities] : this->entitiesMap) {
        this->deleteDeadEntities(entities);
    }
}

auto EntityManager::addEntity(EntityKind entityKind) -> RC<Entity> {
    auto newEntity = RC_NEW<Entity>(this->totalEntities++, entityKind);

    this->entitiesToAdd.push_back(newEntity);

    // Add entity to entitiesMap.
    auto currentEntitiesBasedOnThisKind = this->entitiesMap[entityKind];
    currentEntitiesBasedOnThisKind.push_back(newEntity);
    this->entitiesMap.insert_or_assign(entityKind, currentEntitiesBasedOnThisKind);

    return newEntity;
}

auto EntityManager::getPlayer() -> OPT<RC<Entity>> {
    OPT<RC<Entity>> player = {};

    for (const auto& entity : this->getEntities()) {
        if (entity.has_value()) {
            if (entity.value()->getKind() == EntityKind::Player) {
                player = entity;
            }
        }
    }

    return player;
}

auto EntityManager::getEntities() -> const VEC<OPT<RC<Entity>>>& {
    return this->entities;
}

auto EntityManager::getEntitiesBasedOnKind(EntityKind entityKind) -> const VEC<OPT<RC<Entity>>>& {
    VEC<OPT<RC<Entity>>> ret = {};

    for (const auto& entity: this->entities) {
        if (entity.has_value()) {
            if (entity.value()->getKind() == entityKind) {
                ret.push_back(entity);
            }
        }
    }

    return std::move(ret);
}

auto EntityManager::deleteDeadEntities(VEC<OPT<RC<Entity>>>& entityVec) -> void {
    std::remove_if(entityVec.begin(), entityVec.end(), [](OPT<RC<Entity>> entity) {
        return !entity.value()->isAlive();
    });
}

auto EntityManager::getReservedPositions() -> VEC<Vec2f>& {
    return this->reservedPositions;
}

auto EntityManager::addReservedPosition(Vec2f position) -> void {
    this->reservedPositions.push_back(position);
}
