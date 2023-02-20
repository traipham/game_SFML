#pragma once

#include <iostream>
#include <vector>
#include <ctime>
#include <sstream> // String stream we can mix data types into string
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
	sf::RenderWindow* window; // pointer bc we want to dynamically allocate memory and close window when we want to
	sf::VideoMode videoMode;
	sf::Event ev; // Listener for events: onhover, onClick, onActive, etc

	// Mouse Position
	sf::Vector2i mousePosWindow; // Mouse position of window
	sf::Vector2f mousePosView; 

	// Resources
	sf::Font font;

	// Text
	sf::Text uiText;

	// Game Logic
	bool endGame;
	unsigned points; // Keep track of amount of points
	int health;
	float enemySpawnTimer;
	float enemySpawnTimerMax;
	int maxEnemies; // Max number of enemies on screen at the same time 
	bool mouseHeld;


	// Game objects
	std::vector<sf::RectangleShape> enemies;
	sf::RectangleShape enemy; // Premade texture in SFML


	// Private functions
	void initVariables();
	void initFonts();
	void initText();
	void initWindow();
	void initEnemies();

public:
	// Constructor
	Game();

	// Destructor
	virtual ~Game();

	// Accessors
	const bool running() const;
	const bool getEndGame() const;
	// Functions
	void spawnEnemies();

	void pollEvents();
	void updateMousePosition();
	void updateEnemies();
	void updateText();
	void update(); // TIP: CTRL + . to define function in .cpp file
	
	void renderText(sf::RenderTarget& target);
	void renderEnemies(sf::RenderTarget& target);
	void render();
};

//#endif
