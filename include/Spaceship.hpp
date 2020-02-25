#pragma once
#ifndef _SPACESHIP_
#define _SPACESHIP_

#include "Entity.hpp"
#include "ResourceHolder.hpp"



class Spaceship : Entity {

public:
	enum Type {
		Player1,	Player2,	Player3,
		Enemy1,		Enemy2,		Enemy3
	};
public:
	explicit Spaceship(Type, const TextureHolder&);
	virtual void drawCurrent(sf::RenderTarget&, sf::RenderStates) const;
	Textures::ID toTextureID(Type);
private:
	Type mType;
	sf::Sprite mSprite;
};

Textures::ID toTextureID(Spaceship::Type);

#endif // _SPACESHIP_
