#include "Game.h"

// Private functions
void Game::initVariables() {
	this->window = nullptr;
}

void Game::initWindow() {
	this->videoMode.height = 720;
	this->videoMode.width = 1280;
	// this->videoMode.desktop
	this->window = new sf::RenderWindow(this->videoMode, "My First Game", sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize);

}

// Constructor
Game::Game() {
	this->initVariables();
	this->initWindow();
}

// Destructor
Game::~Game() {
	delete this->window; // Always remember to delete pointer
}

const bool Game::running() const
{
	return this->window->isOpen();
}

// Functions

void Game::pollEvents(){
	while (this->window->pollEvent(ev)) { // whenever window get event, we're going to save into ev Event object
		switch (ev.type) {
		case sf::Event::Closed: // If closed event is called, close window
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (ev.key.code == sf::Keyboard::Escape) { // Keyboard Input = Esc
				this->window->close();
			}
			break;
		}
	}
}

void Game::update() {
	this->pollEvents();
}

/*
* 
*  - clear old frame
*  - render objects
*  - display frame in window
*  @param {} var_name - description
*  @return void
*/
void Game::render() {


	this->window->clear(sf::Color(255, 0, 0, 255)); // Clear old frame

	// Draw game objects

	this->window->display(); // Tell app that window is done drawing
}

