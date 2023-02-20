#include <iostream>
#include "Game.h"
#include <SFML/Audio.hpp>;
// using namespace sf;

int main() {
	std::srand(static_cast<unsigned>(time(NULL)));
	// Create a window
		// sf::VideoMode(width, height) = keeps track of size
		// sf::Window varName(videoMode(sizeWidth, sizeHeight), "title", Style); 
			// sf::Style::Default comes with minimize, fullscreen, exit button, resizing possible (don't want)

	// Init Game Engine
	Game game;
	sf::Music music;
	if (!music.openFromFile("Music/Johan_Vandegriff_Hyperspace.wav"))
	{
		return -1;
	}
	music.play();
	// Game loop
	while (game.running() && !game.getEndGame()) {

		// Update
		game.update();

		// Render
		game.render();
	}
	return 0;
}