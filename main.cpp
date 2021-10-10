#include <iostream>
#include "Game.h"
// using namespace sf;

int main() {
	std::srand(static_cast<unsigned>(time(NULL)));
	// Create a window
		// sf::VideoMode(width, height) = keeps track of size
		// sf::Window varName(videoMode(sizeWidth, sizeHeight), "title", Style); 
			// sf::Style::Default comes with minimize, fullscreen, exit button, resizing possible (don't want)

	// Init Game Engine
	Game game;

	// Game loop
	while (game.running() && !game.getEndGame()) {
		// Event polling

		// Update
		game.update();

		// Render
		game.render();
	}
	return 0;
}