#include <memory>
#include <format>

#include "game.hpp"


Game::Game() {
    this->init();
}

auto Game::init() -> void {
    this->window.create(sf::VideoMode(this->windowWidth, this->windowHeight), "Geometry Wars");
    this->window.setFramerateLimit(60);

    if (!this->font.loadFromFile("../fonts/tech_regular.ttf")) {
        Utils::panic("Failed to load font.");
    }

    this->text.setFont(this->font);

    this->spawnPlayer();
    this->spawnEnemy();
}

auto Game::run() -> void {
    while (!this->paused && this->window.isOpen()) {
        this->entityManager.update(); // Updates the world state on each frame.

        this->enemySpawnerSystem();
        this->collisionSystem();
        this->movementSystem();

        this->renderSystem();
    }
}

auto Game::pause() -> void {
    this->paused = true;
}

auto Game::resume() -> void {
    this->paused = false;
}

auto Game::movementSystem() -> void {
    auto player = Utils::unwrap(this->player, "Player is null at movementSystem()");

    auto playerRadius = player->shapeComponent->shape.getRadius();

    player->transformComponent->velocity.x = 0;
    player->transformComponent->velocity.y = 0;

    auto inputVector = Vec2f(0.f, 0.f);

    if (player->inputComponent->up) {
        if (player->transformComponent->position.y - playerRadius > 0) {
            inputVector.y = -1.f;
        }
    }
    if (player->inputComponent->down) {
        if (player->transformComponent->position.y + playerRadius < this->windowHeight) {
            inputVector.y = 1.f;
        }
    }
    if (player->inputComponent->left) {
        if (player->transformComponent->position.x - playerRadius > 0) {
            inputVector.x = -1.f;
        }
    }
    if (player->inputComponent->right) {
        if (player->transformComponent->position.x + playerRadius < this->windowWidth) {
            inputVector.x = 1.f;
        }
    }

    const auto playerSpeed = 8.f;

    player->transformComponent->velocity.x = inputVector.normalize().x * playerSpeed;
    player->transformComponent->velocity.y = inputVector.normalize().y * playerSpeed;

    player->transformComponent->position.x += player->transformComponent->velocity.x;
    player->transformComponent->position.y += player->transformComponent->velocity.y;
}

auto Game::userInputSystem(const sf::Event& event) -> void {
    auto player = Utils::unwrap(this->player, "Player is null at userInputSystem()");

    // Keyboard events.
    if (event.type == sf::Event::KeyPressed) {
        // Player movement.
        if (event.key.code == sf::Keyboard::W) {
            player->inputComponent->up = true;
        }
        if (event.key.code == sf::Keyboard::S) {
            player->inputComponent->down = true;
        }
        if (event.key.code == sf::Keyboard::A) {
            player->inputComponent->left = true;
        }
        if (event.key.code == sf::Keyboard::D) {
            player->inputComponent->right = true;
        }
    }
    if (event.type == sf::Event::KeyReleased) {
        if (event.key.code == sf::Keyboard::W) {
            player->inputComponent->up = false;
        }
        if (event.key.code == sf::Keyboard::S) {
            player->inputComponent->down = false;
        }
        if (event.key.code == sf::Keyboard::A) {
            player->inputComponent->left = false;
        }
        if (event.key.code == sf::Keyboard::D) {
            player->inputComponent->right = false;
        }
    }
    // Mouse events.
    if (event.type == sf::Event::MouseButtonPressed) {
        auto sfPosition = sf::Mouse::getPosition(this->window);
        auto position = Vec2f(CASTF(sfPosition.x), CASTF(sfPosition.y));

        this->spawnBullet(player, position);
    }
}

auto Game::lifespanSystem() -> void {

}

// Responsible for rendering each frame. Will get called every frame.
auto Game::renderSystem() -> void {
    this->window.clear(sf::Color(0, 0, 0));

    sf::Event event;
    while (this->window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            this->window.close();
        } else if (event.type == sf::Event::Resized) {
            // TODO: Figure out resizing.
        }

        this->userInputSystem(event);
    }

    for (const auto& entity : this->entityManager.getEntities()) {
        if (entity.has_value()) {
            const auto& entityVal = entity.value();

            entityVal->shapeComponent->shape.setPosition(entityVal->transformComponent->position.x,
                                                      entityVal->transformComponent->position.y);

            entityVal->transformComponent->angle += 1.f;
            entityVal->shapeComponent->shape.setRotation(entityVal->transformComponent->angle);

            this->window.draw(entityVal->shapeComponent->shape);
        }
    }


    this->currentFrame++;
    this->window.display();
}

auto Game::enemySpawnerSystem() -> void {
    // Spawn an enemy every 2 seconds.
    if (this->currentFrame != 0 && this->currentFrame % this->enemySpawnRateInFrames == 0) {
        this->spawnEnemy();
    }
}

auto Game::collisionSystem() -> void {

}

auto Game::spawnPlayer() -> void {
    auto playerEntity = this->entityManager.addEntity(EntityKind::Player);
    // Give the playerEntity a transform component so that it spawns at the center with a velocity of (1, 1) and an angle of 0.
    auto middleX = CASTF(this->window.getSize().x) / 2;
    auto middleY = CASTF(this->window.getSize().y) / 2;
    auto playerPosition = Vec2f(middleX, middleY);
    playerEntity->transformComponent = RC_NEW<TransformComponent>(playerPosition, Vec2f(1.f, 1.f), 0.f);
    this->entityManager.addReservedPosition(playerPosition);
    // Define the players shape by giving it a shape component.
    playerEntity->shapeComponent = RC_NEW<ShapeComponent>(
        32.f,
        32,
        sf::Color(10, 10, 10),
        sf::Color(255, 0, 0),
        4.f
    );
    // Set the playerEntity to be always on top of other entities.
    // playerEntity->shapeComponent->shape.

    playerEntity->inputComponent = RC_NEW<InputComponent>();

    this->player = playerEntity;
}

auto Game::spawnEnemy() -> void {
    auto newEntity = this->entityManager.addEntity(EntityKind::Enemy);

    auto randomPointCount    = Utils::randomInt(3,   8);
    auto randomFillColorR    = Utils::randomInt(0, 255);
    auto randomFillColorG    = Utils::randomInt(0, 255);
    auto randomFillColorB    = Utils::randomInt(0, 255);
    auto randomOutlineColorR = Utils::randomInt(0, 255);
    auto randomOutlineColorG = Utils::randomInt(0, 255);
    auto randomOutlineColorB = Utils::randomInt(0, 255);

    newEntity->shapeComponent = RC_NEW<ShapeComponent>(
            32.f,
            randomPointCount,
            sf::Color(randomFillColorR, randomFillColorG, randomFillColorB),
            sf::Color(randomOutlineColorR, randomOutlineColorG, randomOutlineColorB),
            4.f
    );

    auto randomX = Utils::randomReal<float>(
        newEntity->shapeComponent->shape.getRadius() * 2,
        this->window.getSize().x - newEntity->shapeComponent->shape.getRadius() * 2
    );
    auto randomY = Utils::randomReal<float>(
        newEntity->shapeComponent->shape.getRadius() * 2,
        this->window.getSize().y - newEntity->shapeComponent->shape.getRadius() * 2
    );

    // BUG: Enemies are spawning on top of each other and the player.

    auto randomPosition = Vec2f(randomX, randomY);

    this->entityManager.addReservedPosition(randomPosition);
    this->lastEntitySpawnPosition = randomPosition;
    newEntity->transformComponent = RC_NEW<TransformComponent>(randomPosition, Vec2f(0.f, 0.f), 0.f);


    // Record the frame that the enemy was spawned on.
    this->lastEnemySpawnFrame = this->currentFrame;
}

auto Game::spawnSmallEnemies(RC<Entity> entity) -> void {

}

auto Game::spawnBullet(RC<Entity> player, const Vec2f &targetPos) -> void {
    auto direction = Vec2f(CASTF(targetPos.x), CASTF(targetPos.y)) - player->transformComponent->position;

    auto bullet= this->entityManager.addEntity(EntityKind::Bullet);

    bullet->shapeComponent = RC_NEW<ShapeComponent>(
        2.f,
        32,
        sf::Color(255, 255, 255),
        sf::Color(255, 255, 255),
        1.f
    );

    bullet->transformComponent = RC_NEW<TransformComponent>(
        player->transformComponent->position,
        direction.normalize() * 8.f,
        0.f
    );
}

auto Game::spawnSpecialWeapon(RC<Entity> entity) -> void {

}
