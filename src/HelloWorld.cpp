#include <SFML\Graphics.hpp>
#include <iostream>
#include <assert.h>

constexpr auto SpriteSpeed = 300;
constexpr auto WindowWidth = 1200;
constexpr auto WindowHeigth = 600;
constexpr auto FramesPerSecond = 60.f;
const auto TimePerFrame = sf::seconds(1.f / FramesPerSecond);

namespace Textures {
	enum ID {Landscape=1, Missile=2, Spaceship=3};
}

template<typename Resource, typename Identifier>
class ResourceHolder {
public:
	void load(Identifier, const std::string&);
	Resource& get(Identifier);
	const Resource& get(Identifier) const; 
private:
	std::map<Identifier, std::unique_ptr<Resource>> mResourceMap;
};

template<typename Resource, typename Identifier>
void ResourceHolder<Resource, Identifier>::load(Identifier id, const std::string& filename){
	std::unique_ptr<Resource> resource(new Resource());
	if (!resource->loadFromFile(filename))
		throw std::runtime_error("ResourceHolder::load failed to load " + filename);

	auto inserted = mResourceMap.insert(std::make_pair(id, std::move(resource)));
	
	assert(inserted.second);
}

template<typename Resource, typename Identifier>
Resource& ResourceHolder<Resource, Identifier>::get(Identifier id) {
	auto found = mResourceMap.find(id);
	assert(found != mResourceMap.end());
	return *found->second;
}

template<typename Resource, typename Identifier>
const Resource& ResourceHolder<Resource, Identifier>::get(Identifier id) const {
	auto found = mResource.find(id);
	assert(found != mResourceMap.end());
	return *found->second;
}

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

int main() {
	try {
		Game myGame;
		myGame.run();
	}
	catch (std::exception& e) {
		std::cout << "\n"<< e.what() << std::endl;
		(void) getchar();
	}
	
}