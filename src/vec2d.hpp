#pragma once

class Vec2f {
public:
    float x = {};
    float y = {};

    Vec2f() = default;

    Vec2f(float x, float y);

    [[nodiscard]] auto operator==(const Vec2f &rhs) const -> bool;

    [[nodiscard]] auto operator!=(const Vec2f &rhs) const -> bool;

    [[nodiscard]] auto operator+(const Vec2f &rhs) const -> Vec2f;

    [[nodiscard]] auto operator-(const Vec2f &rhs) const -> Vec2f;

    [[nodiscard]] auto operator/(const float val) const -> Vec2f;

    [[nodiscard]] auto operator*(const float val) const -> Vec2f;

    auto operator+=(const Vec2f &rhs) -> void;

    auto operator-=(const Vec2f &rhs) -> void;

    auto operator*=(const float val) -> void;

    auto operator/=(const float val) -> void;

    [[nodiscard]] auto length() const -> float;

    [[nodiscard]] auto distanceTo(const Vec2f &rhs) const -> float;

    [[nodiscard]] auto normalize() const -> Vec2f;
};