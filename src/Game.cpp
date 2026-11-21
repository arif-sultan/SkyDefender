#include "../include/Game.hpp"
#include <sstream>

const float WINDOW_WIDTH = 800.0f;
const float WINDOW_HEIGHT = 600.0f;

Game::Game()
    // VideoMode takes a sf::Vector2u ({800, 600}) instead of two separate ints
    : window(sf::VideoMode({800, 600}), "Sky Defender: Kryptonian Reef"),
      fontLoaded(false),
      state(GameState::MainMenu),
      player(100, 300.0f, 3, 2, 375.0f, 500.0f),
      enemyManager(WINDOW_WIDTH, WINDOW_HEIGHT),
      selectedWeapon(0),
      equippedWeapon(0),
      score(0),
      credits(1000),
      stage(1),
      damageTimer(0.0f)
{
    window.setFramerateLimit(60);

    // Audio is optional: playback starts only when these files exist.
    audio.playMusic("assets/background.ogg");
    audio.playShootSound("assets/shoot.wav");

    // The font is optional. The game still runs if this file is unavailable.
    fontLoaded = font.openFromFile("assets/arial.ttf");
    if (!fontLoaded)
        fontLoaded = font.openFromFile("C:/Windows/Fonts/arial.ttf");

    // Weapon values: name, damage, cooldown, ammo, purchase cost.
    weapons.push_back(Weapon("Plasma Gatling", 10, 0.20f, -1, 0));
    weapons.push_back(Weapon("Proton Cannon", 30, 0.65f, -1, 500));
    weapons.push_back(Weapon("Hellfire Rockets", 50, 1.00f, 20, 750));
    weapons.push_back(Weapon("Sonic Pulse", 20, 0.35f, 40, 600));

    weaponOwned.push_back(true); // The basic weapon is already unlocked.
    weaponOwned.push_back(false);
    weaponOwned.push_back(false);
    weaponOwned.push_back(false);
}

void Game::run()
{
    while (window.isOpen())
    {
        handleEvents();

        float deltaTime = gameClock.restart().asSeconds();
        if (deltaTime > 0.05f)
            deltaTime = 0.05f; // Avoid a large jump after a pause.

        update(deltaTime);
        render();
    }
}

void Game::handleEvents()
{
    // pollEvent() returns std::optional<sf::Event>
    while (const std::optional event = window.pollEvent())
    {
        // Event types are checked via is<sf::Event::...>() and accessed via getIf<...>()
        if (event->is<sf::Event::Closed>())
            window.close();

        if (const auto *keyPressed = event->getIf<sf::Event::KeyPressed>())
        {
            const sf::Keyboard::Key key = keyPressed->code;

            if (state == GameState::MainMenu || state == GameState::GameOver ||
                state == GameState::Victory || state == GameState::Controls)
            {
                handleMenuInput(key);
            }
            else if (state == GameState::Playing)
            {
                if (key == sf::Keyboard::Key::Escape)
                    state = GameState::Paused;

                if (key == sf::Keyboard::Key::B && player.useBomb())
                {
                    // A bomb clears the current enemies.
                    score += enemyManager.getActiveCount() * 100;
                    credits += enemyManager.getActiveCount() * 25;
                    enemyManager.clear();
                }
            }
            else if (state == GameState::Paused)
            {
                if (key == sf::Keyboard::Key::Escape ||
                    key == sf::Keyboard::Key::Enter)
                    state = GameState::Playing;
                else if (key == sf::Keyboard::Key::R)
                    startNewGame();
                else if (key == sf::Keyboard::Key::M)
                    state = GameState::MainMenu;
            }
            else if (state == GameState::Hangar)
            {
                if (key == sf::Keyboard::Key::Escape)
                    state = GameState::MainMenu;
                else if (key == sf::Keyboard::Key::Up)
                    selectedWeapon = (selectedWeapon + (int)weapons.size() - 1) % (int)weapons.size();
                else if (key == sf::Keyboard::Key::Down)
                    selectedWeapon = (selectedWeapon + 1) % (int)weapons.size();
                else if (key == sf::Keyboard::Key::B)
                {
                    if (!weaponOwned[selectedWeapon] &&
                        credits >= weapons[selectedWeapon].getCost())
                    {
                        credits -= weapons[selectedWeapon].getCost();
                        weaponOwned[selectedWeapon] = true;
                    }
                }
                else if (key == sf::Keyboard::Key::E &&
                         weaponOwned[selectedWeapon])
                {
                    equippedWeapon = selectedWeapon;
                }
            }
        }
    }
}

void Game::handleMenuInput(sf::Keyboard::Key key)
{
    //  Scoped enum sf::Keyboard::Key::...
    if (state == GameState::MainMenu)
    {
        if (key == sf::Keyboard::Key::Num1 || key == sf::Keyboard::Key::Enter)
            startNewGame();
        else if (key == sf::Keyboard::Key::Num2)
            state = GameState::Hangar;
        else if (key == sf::Keyboard::Key::Num3)
            state = GameState::Controls;
        else if (key == sf::Keyboard::Key::Escape || key == sf::Keyboard::Key::Num4)
            window.close();
    }
    else if (state == GameState::GameOver || state == GameState::Victory)
    {
        if (key == sf::Keyboard::Key::Enter || key == sf::Keyboard::Key::R)
            startNewGame();
        else if (key == sf::Keyboard::Key::M || key == sf::Keyboard::Key::Escape)
            state = GameState::MainMenu;
    }
    else if (state == GameState::Controls)
    {
        if (key == sf::Keyboard::Key::Escape || key == sf::Keyboard::Key::Enter)
            state = GameState::MainMenu;
    }
}

void Game::startNewGame()
{
    player = Aircraft(100, 300.0f, 3, 2, 375.0f, 500.0f);
    enemyManager.clear();
    enemyManager.setStage(1);
    projectiles.clear();
    score = 0;
    stage = 1;
    damageTimer = 0.0f;
    state = GameState::Playing;
}

void Game::update(float deltaTime)
{
    if (state == GameState::Playing)
        updateGameplay(deltaTime);
}

void Game::updateGameplay(float deltaTime)
{
    player.handleInput(deltaTime, WINDOW_WIDTH, WINDOW_HEIGHT);
    weapons[equippedWeapon].update(deltaTime);

    // Hold Space to fire the currently equipped weapon.
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
    {
        sf::FloatRect aircraft = player.getBounds();
        // FloatRect uses .position.x/y and .size.x/y instead of .left/.top/.width/.height
        float x = aircraft.position.x + aircraft.size.x / 2.0f - 3.0f;
        float y = aircraft.position.y;
        if (weapons[equippedWeapon].canFire())
        {
            weapons[equippedWeapon].fire(x, y, projectiles);
            audio.playShoot();
        }
    }

    enemyManager.update(deltaTime);

    for (std::size_t i = 0; i < projectiles.size();)
    {
        projectiles[i].update(deltaTime);
        if (!projectiles[i].isActive())
            projectiles.erase(projectiles.begin() + i);
        else
            ++i;
    }

    checkCollisions();
    int pointsEarned = enemyManager.removeDefeated();
    score += pointsEarned;
    credits += pointsEarned / 4; // Defeating enemies also earns hangar credits.
    damageTimer -= deltaTime;

    if (score >= 1000)
        state = GameState::Victory;
    if (!player.isAlive())
        state = GameState::GameOver;
}

void Game::checkCollisions()
{
    // Projectile-versus-enemy collision.
    for (std::size_t p = 0; p < projectiles.size(); ++p)
    {
        if (!projectiles[p].isActive())
            continue;

        for (int e = 0; e < enemyManager.getActiveCount(); ++e)
        {
            Enemy *enemy = enemyManager.getEnemy(e);
            if (enemy == nullptr)
                continue;

            // FloatRect takes two Vector2f arguments: position and size
            sf::FloatRect enemyBounds(
                {enemy->getLeft(), enemy->getTop()},
                {enemy->getWidth(), enemy->getHeight()});

            // intersects() is now findIntersection() (returns std::optional<sf::FloatRect>)
            if (projectiles[p].getBounds().findIntersection(enemyBounds).has_value())
            {
                enemy->takeDamage(projectiles[p].getDamage());
                projectiles[p].deactivate();
                break;
            }
        }
    }

    // Aircraft-versus-enemy collision. A short timer prevents constant damage.
    if (damageTimer <= 0.0f)
    {
        for (int e = 0; e < enemyManager.getActiveCount(); ++e)
        {
            Enemy *enemy = enemyManager.getEnemy(e);
            if (enemy == nullptr)
                continue;

            sf::FloatRect enemyBounds(
                {enemy->getLeft(), enemy->getTop()},
                {enemy->getWidth(), enemy->getHeight()});

            if (player.getBounds().findIntersection(enemyBounds).has_value())
            {
                player.takeDamage(enemy->getDamageOnCollision());
                damageTimer = 1.0f;
                break;
            }
        }
    }
}

void Game::drawText(const std::string &value, float x, float y,
                    unsigned int size, sf::Color color)
{
    if (!fontLoaded)
        return;

    // sf::Text constructor requires (font, string, size) in that order
    sf::Text text(font, value, size);
    text.setFillColor(color);
    // setPosition takes a single sf::Vector2f ({x, y})
    text.setPosition({x, y});
    window.draw(text);
}

void Game::drawButton(const std::string &label, float x, float y,
                      float width, float height, bool selected)
{
    sf::RectangleShape button(sf::Vector2f(width, height));
    button.setPosition({x, y});
    button.setFillColor(selected ? sf::Color(25, 120, 150) : sf::Color(20, 55, 85));
    button.setOutlineThickness(2.0f);
    button.setOutlineColor(sf::Color::Cyan);
    window.draw(button);
    drawText(label, x + 15.0f, y + 8.0f, 22);
}

void Game::drawMainMenu()
{
    drawText("SKY DEFENDER", 235, 100, 42, sf::Color::Cyan);
    drawText("KRYPTONIAN REEF", 270, 155, 24);
    drawButton("1. Start Game", 280, 250, 240, 45, true);
    drawButton("2. Weapons Hangar", 280, 310, 240, 45, false);
    drawButton("3. Controls", 280, 370, 240, 45, false);
    drawButton("4. Exit", 280, 430, 240, 45, false);
    drawText("Choose an option using the number keys.", 210, 510, 18);
}

void Game::drawHangar()
{
    drawText("WEAPONS HANGAR", 250, 35, 34, sf::Color::Cyan);

    std::ostringstream info;
    info << "Credits: " << credits;
    drawText(info.str(), 40, 100, 22, sf::Color::Yellow);

    for (std::size_t i = 0; i < weapons.size(); ++i)
    {
        std::ostringstream line;
        line << weapons[i].getName() << "   Damage: " << weapons[i].getDamage()
             << "   Cost: " << weapons[i].getCost();

        if (weaponOwned[i])
            line << "   [OWNED]";
        else
            line << "   [LOCKED]";

        drawButton(line.str(), 55, 155 + (float)i * 65.0f,
                   690, 48, (int)i == selectedWeapon);
    }

    drawText("UP/DOWN: Select    B: Buy    E: Equip    ESC: Back",
             75, 465, 18, sf::Color::Yellow);
    drawText("Equipped: " + weapons[equippedWeapon].getName(), 75, 515, 20);
}

void Game::drawEnemies()
{
    for (int i = 0; i < enemyManager.getActiveCount(); ++i)
    {
        Enemy *enemy = enemyManager.getEnemy(i);
        if (enemy == nullptr)
            continue;

        sf::RectangleShape enemyShape(
            sf::Vector2f(enemy->getWidth(), enemy->getHeight()));
        // setOrigin and setPosition take sf::Vector2f ({x, y})
        enemyShape.setOrigin({enemy->getWidth() / 2.0f, enemy->getHeight() / 2.0f});
        enemyShape.setPosition({enemy->getPosition().getX(),
                                enemy->getPosition().getY()});
        enemyShape.setFillColor(enemy->isBoss() ? sf::Color::Red : sf::Color(230, 100, 70));
        enemyShape.setOutlineThickness(2.0f);
        enemyShape.setOutlineColor(sf::Color::Yellow);
        window.draw(enemyShape);
    }
}

void Game::drawGameplay()
{
    drawEnemies();

    for (std::size_t i = 0; i < projectiles.size(); ++i)
        projectiles[i].render(window);

    player.render(window);

    std::ostringstream status;
    status << "Score: " << score << "   Lives: " << player.getLives()
           << "   Health: " << player.getHealth()
           << "   Bombs: " << player.getBombs()
           << "   Stage: " << stage;
    drawText(status.str(), 15, 10, 18, sf::Color::White);
    drawText("SPACE: Fire   B: Bomb   ESC: Pause", 15, 575, 16);
}

void Game::drawPauseMenu()
{
    drawGameplay();
    sf::RectangleShape overlay(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
    overlay.setFillColor(sf::Color(0, 0, 0, 180));
    window.draw(overlay);
    drawText("PAUSED", 325, 190, 42, sf::Color::Cyan);
    drawText("ENTER / ESC: Resume", 285, 285, 22);
    drawText("R: Restart", 330, 330, 22);
    drawText("M: Main Menu", 315, 375, 22);
}

void Game::drawEndScreen(bool victory)
{
    drawText(victory ? "VICTORY!" : "GAME OVER",
             270, 180, 44, victory ? sf::Color::Green : sf::Color::Red);
    drawText("Final Score: " + std::to_string(score), 300, 260, 24);
    drawText("ENTER / R: Play Again", 275, 340, 20);
    drawText("M / ESC: Main Menu", 285, 390, 20);
}

void Game::drawControls()
{
    drawText("CONTROLS", 305, 100, 36, sf::Color::Cyan);
    drawText("Arrow Keys or WASD : Move aircraft", 180, 220, 22);
    drawText("SPACE : Fire weapon", 180, 270, 22);
    drawText("B : Use bomb", 180, 320, 22);
    drawText("ESC : Pause the game", 180, 370, 22);
    drawText("Press ENTER or ESC to return.", 205, 470, 20);
}

void Game::render()
{
    window.clear(sf::Color(8, 28, 55));

    if (state == GameState::MainMenu)
        drawMainMenu();
    else if (state == GameState::Hangar)
        drawHangar();
    else if (state == GameState::Playing)
        drawGameplay();
    else if (state == GameState::Paused)
        drawPauseMenu();
    else if (state == GameState::GameOver)
        drawEndScreen(false);
    else if (state == GameState::Victory)
        drawEndScreen(true);
    else if (state == GameState::Controls)
        drawControls();

    window.display();
}