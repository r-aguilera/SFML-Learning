#pragma once
#ifndef _SPACESHIP_
#define _SPACESHIP_

#include "Entity.hpp"

class Spaceship : Entity {
public:
	explicit Spaceship(mType);
public:
	enum Type {
		Player1,	Player2,	Player3,
		Enemy1,		Enemy2,		Enemy3,
	};
private:
	Type mType;
};

#endif // _SPACESHIP_
