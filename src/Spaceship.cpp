#include "Spaceship.hpp"

Spaceship::Spaceship(Type type, const TextureHolder& textures) : 
	mType(type),
	mSprite(textures.get(toTextureID(type)))
{
	sf::FloatRect bounds = mSprite.getLocalBounds();
	mSprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

void Spaceship::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(mSprite, states);
}

Textures::ID toTextureID(Spaceship::Type type) {
	switch (type) {
	case Spaceship::Player1:
		return Textures::Player1;
		break;
	case Spaceship::Player2:
		return Textures::Player2;
		break;
	case Spaceship::Player3:
		return Textures::Player3;
		break;
	case Spaceship::Enemy1:
		return Textures::Enemy1;
		break;
	case Spaceship::Enemy2:
		return Textures::Enemy2;
		break;
	case Spaceship::Enemy3:
		return Textures::Enemy3;
		break;
	}
}
