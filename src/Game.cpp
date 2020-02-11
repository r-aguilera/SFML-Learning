#include <SFML\Graphics.hpp>
#include "Game.hpp"
#include "identifiers.hpp"
#include "constexprVars.hpp"

Game::Game() :
	mWindow(sf::VideoMode(WindowWidth, WindowHeigth, 32), "This is the title"),
	mTextures(),
	mSprite(),
	mIsMovingRight(false),
	mIsMovingLeft(false),
	mIsMovingUp(false),
	mIsMovingDown(false) {

	mTextures.load(Textures::Spaceship, "../../media/ScratchCat.png");
	mSprite.setTexture(mTextures.get(Textures::Spaceship));
	mSprite.setPosition(200.f, 200.f);
	mSprite.setScale(0.5, 0.5);
}

void Game::run() {
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	while (mWindow.isOpen()) {

		processEvents();
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > TimePerFrame) {
			update(TimePerFrame);
			timeSinceLastUpdate -= TimePerFrame;
		}
		render();
	}
}

void Game::processEvents() {
	sf::Event event;
	while (mWindow.pollEvent(event)) {
		switch (event.type) {
		case sf::Event::KeyPressed:
			handlePlayerInput(event.key.code, true);
			break;
		case sf::Event::KeyReleased:
			handlePlayerInput(event.key.code, false);
			break;
		case sf::Event::Closed:
			mWindow.close();
			break;
		}
	}
}

void Game::render() {
	mWindow.clear();
	mWindow.draw(mSprite);
	mWindow.display();
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed) {
	if (key == sf::Keyboard::D)
		mIsMovingRight = isPressed;
	else if (key == sf::Keyboard::A)
		mIsMovingLeft = isPressed;
	else if (key == sf::Keyboard::W)
		mIsMovingUp = isPressed;
	else if (key == sf::Keyboard::S)
		mIsMovingDown = isPressed;
}

void Game::update(sf::Time dTime) {
	sf::Vector2f movement(0.f, 0.f);
	if (mIsMovingRight)
		movement.x += SpriteSpeed;
	if (mIsMovingLeft)
		movement.x -= SpriteSpeed;
	if (mIsMovingUp)
		movement.y -= SpriteSpeed;
	if (mIsMovingDown)
		movement.y += SpriteSpeed;
	mSprite.move(movement * dTime.asSeconds());
}