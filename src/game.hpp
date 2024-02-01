#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

#include "entity.hpp"
#include "vec2d.hpp"
#include "entityManager.hpp"

//struct PlayerConfig { size_t shapeRadius, collisionRadius, FR, FG, FB, OR, OG, OB, OT, V; float S; };
//struct EnemyConfig { size_t shapeRadius, collisionRadius, OR, OG, OB, OT, VMIN, VMAX, L, SI; float SMIN, SMAX; };
//struct BulletConfig { size_t shapeRadius, collisionRadius, FR, FG, FB, OR, OG, OB, OT, V, L; float S; };

class Game {
public:
    Game();

    auto run() -> void;
private:
    sf::RenderWindow            window;
    sf::Font                    font;
    EntityManager               entityManager = {};
    sf::Text                    text = {};
    const size_t                windowWidth = 1200;
    const size_t                windowHeight = 800;
    size_t                      score = {};
    size_t                      currentFrame = {};
    size_t                      enemySpawnRateInFrames = 60;
    size_t                      lastEnemySpawnFrame = {};
    Vec2f                       lastEntitySpawnPosition = {};
    bool                        paused  = false;
    OPT<RC<Entity>>             player;

    auto init() -> void;

    auto pause() -> void;

    auto resume() -> void;

    auto movementSystem() -> void;

    auto userInputSystem(const sf::Event& event) -> void;

    auto lifespanSystem() -> void;

    auto renderSystem() -> void;

    auto enemySpawnerSystem() -> void;

    auto collisionSystem() -> void;

    auto spawnPlayer() -> void;

    auto spawnEnemy() -> void;

    auto spawnSmallEnemies(RC<Entity> entity) -> void;

    auto spawnBullet(RC<Entity> player, const Vec2f& targetPos) -> void;

    auto spawnSpecialWeapon(RC<Entity> entity) -> void;
};