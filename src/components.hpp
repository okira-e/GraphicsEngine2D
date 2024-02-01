#pragma once

#include <SFML/Graphics.hpp>
#include "vec2d.hpp"

// Holds the data for entity transformations.
class TransformComponent {
public:
    Vec2f position  = {0.0, 0.0};
    Vec2f velocity  = {8.0, 8.0};
    float angle     = 0;

    TransformComponent(Vec2f pos, Vec2f vel, float ang) : position(pos), velocity(vel), angle(ang) {}
};

// The most important component as it holds the final object that will be used by SFML to be rendered.
class ShapeComponent {
public:
    sf::CircleShape shape;

    ShapeComponent(float radius, int pointCount, const sf::Color& colorFill, const sf::Color& colorOutline, float outlineThickness)
    : shape(radius, pointCount)
    {
        shape.setFillColor(colorFill);
        shape.setOutlineColor(colorOutline);
        shape.setOutlineThickness(outlineThickness);
        shape.setOrigin(radius, radius);
    }
};

class CollisionComponent {
public:
    float radius = 0.f;

    CollisionComponent(float r) : radius(r) {}
};

class ScoreComponent {
public:
    size_t score = 0;

    ScoreComponent(size_t s) : score(s) {}
};

class LifespanComponent {
public:
    size_t remainingLives = 0;
    size_t totalLives = 0;

    LifespanComponent(size_t r, size_t t) : remainingLives(r), totalLives(t) {}
};

class InputComponent {
public:
    bool up = false;
    bool down = false;
    bool left = false;
    bool right = false;

    InputComponent() = default;
};