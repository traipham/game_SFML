#pragma once

// Faster to have include in this .h file
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp> // Not nice in SFML

//#ifndef GAME_H
//#define GAME_H

/*
* Game Engine class
* Wrapper class
*/
class Game {
private:

	// Variables
	// Window
	sf::RenderWindow* window; // pointer bc we want to dynamically allocate memory and close it when we want to
	sf::VideoMode videoMode;
	sf::Event ev; // Listener for events: onhover, onClick, onActive, etc

	void initVariables();
	void initWindow();

public:
	// Constructor
	Game();

	// Destructor
	virtual ~Game();

	// Accessors
	const bool running() const;

	// Functions
	void pollEvents();
	void update(); // TIP: CTRL + . to define function in .cpp file
	void render();
};

//#endif
