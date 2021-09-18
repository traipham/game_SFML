#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp> // Not nice in SFML

// using namespace sf;

int main() {

	// Create a window
		// sf::VideoMode(width, height) = keeps track of size
		// sf::Window varName(videoMode(sizeWidth, sizeHeight), "title", Style); 
			// sf::Style::Default comes with minimize, fullscreen, exit button, resizing possible (don't want)
	sf::RenderWindow window(sf::VideoMode(640, 480), "My First Game", sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize);
	sf::Event ev; // Listener for events: onhover, onClick, onActive, etc

	// Game loop
	while (window.isOpen()) 
	{
		// Event polling
		while (window.pollEvent(ev)) // whenever window get event, we're going to save into ev Event object
		{
			switch (ev.type)
			{
			case sf::Event::Closed: // If closed event is called, close window
				window.close();
				break;
			case sf::Event::KeyPressed:
				if (ev.key.code == sf::Keyboard::Escape)
				{
					window.close();
				}
				break;
			}
		}

		// Update

		// Render
		window.clear(); // Clear old frame

		// Draw game


		window.display(); // Tell app that window is done drawing

	}
	return 0;
}