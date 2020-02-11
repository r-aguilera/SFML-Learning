#include <SFML\Graphics.hpp>
#include "Game.hpp"
#include <iostream>

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