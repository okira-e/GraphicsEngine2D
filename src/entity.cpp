#include "entity.hpp"


Entity::Entity(size_t id, EntityKind kind) : id(id), kind(kind)
{}

auto Entity::isAlive() const -> bool {
    return this->alive;
}

auto Entity::getKind() const -> const EntityKind & {
    return this->kind;
}

auto Entity::getId() const -> const size_t {
    return this->id;
}

auto Entity::destroy() -> void {
    this->alive = false;
}
