#pragma once

#include <iostream>
#include <memory>

#include "components.hpp"
#include "utils.hpp"

enum EntityKind {
    Player,
    Enemy,
    Bullet,
};

class Entity {
public:

    // Components
    RC<TransformComponent> transformComponent   = {};
    RC<ShapeComponent>     shapeComponent       = {};
    RC<CollisionComponent> collisionComponent   = {};
    RC<InputComponent>     inputComponent       = {};
    RC<ScoreComponent>     scoreComponent       = {};
    RC<LifespanComponent>  lifespanComponent    = {};

    Entity(size_t id, EntityKind kind);

    auto isAlive() const -> bool;

    auto getKind() const -> const EntityKind&;

    auto getId() const -> const size_t;

    auto destroy() -> void;

private:
    bool alive = true;
    size_t id = {};
    EntityKind kind = {};
};
