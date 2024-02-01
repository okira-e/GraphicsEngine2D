#include "vec2d.hpp"
#include <cmath>
#include <tuple>

Vec2f::Vec2f(float x, float y) : x(x), y(y) {}

auto Vec2f::operator==(const Vec2f &rhs) const -> bool {
    return this->x == rhs.x && this->y == rhs.y;
}

auto Vec2f::operator!=(const Vec2f &rhs) const -> bool {
    return !(rhs == *this);
}

auto Vec2f::operator+(const Vec2f &rhs) const -> Vec2f {
    auto ret = Vec2f();
    ret.x = this->x + rhs.x;
    ret.y = this->y + rhs.y;

    return ret;
}

auto Vec2f::operator-(const Vec2f &rhs) const -> Vec2f {
    auto ret = Vec2f();
    ret.x = this->x - rhs.x;
    ret.y = this->y - rhs.y;

    return ret;
}

auto Vec2f::operator/(const float val) const -> Vec2f {
    auto ret = Vec2f();
    ret.x = this->x / val;
    ret.y = this->y / val;

    return ret;
}

auto Vec2f::operator*(const float val) const -> Vec2f {
    auto ret = Vec2f();
    ret.x = this->x * val;
    ret.y = this->y * val;

    return ret;
}

auto Vec2f::operator+=(const Vec2f &rhs) -> void {
    *this = *this + rhs;
}

auto Vec2f::operator-=(const Vec2f &rhs) -> void {
    *this = *this - rhs;
}

auto Vec2f::operator*=(const float val) -> void {
    *this = *this * val;
}

auto Vec2f::operator/=(const float val) -> void {
    *this = *this / val;
}

// Returns the length of the vector.
auto Vec2f::length() const -> float {
    return std::sqrt(this->x * this->x + this->y * this->y);
}

// Returns the distanceTo between two vectors.
auto Vec2f::distanceTo(const Vec2f &rhs) const -> float {
    auto differenceInX = std::abs(rhs.x - this->x);
    auto differenceInY = std::abs(rhs.y - this->y);

    return std::sqrt(differenceInX * differenceInX + differenceInY * differenceInY);
}

// Returns the normalized vector.
auto Vec2f::normalize() const -> Vec2f {
    auto length = this->length();

    if (length == 0) {
        return Vec2f();
    }

    return *this / length;
}
