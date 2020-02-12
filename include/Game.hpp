#pragma once
#ifndef _GAME_
#define _GAME_

#include <SFML\Graphics.hpp>
#include "ResourceHolder.hpp"
#include "identifiers.hpp"

class Game {
public:
	Game();
	void run();
private:
	void update(sf::Time);
	void processEvents();
	void render();
	void handlePlayerInput(sf::Keyboard::Key, bool);
private:
	sf::RenderWindow mWindow;
	ResourceHolder<sf::Texture, Textures::ID> mTextures;
	sf::Sprite mSprite;
	bool mIsMovingRight;
	bool mIsMovingLeft;
	bool mIsMovingUp;
	bool mIsMovingDown;
};

#endif // _GAME_
