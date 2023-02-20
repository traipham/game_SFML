#include "Game.h"

// Private functions
void Game::initVariables() {
	this->window = nullptr;

	// Game Logics
	//int points; // Keep track of amount of points
	//float enemySpawnTimer;
	//float enemySpawnTimerMax;
	//int maxEnemies;
	this->endGame = false;
	this->points = 0;
	this->health = 20;
	this->enemySpawnTimerMax = 20.f;
	this->enemySpawnTimer = this->enemySpawnTimerMax;
	this->maxEnemies = 5;
	this->mouseHeld = false;
}

void Game::initFonts()
{
	if (!this->font.loadFromFile("Fonts/Staatliches-Regular.ttf")) 	// load fonts
	{
		std::cout << "ERROR::GAME::INITFONTS::Failed to load font!" << "\n";
	}
}

void Game::initText()
{
	this->uiText.setFont(this->font); // set font for text
	this->uiText.setCharacterSize(24);
	this->uiText.setFillColor(sf::Color::Black);
	this->uiText.setStyle(sf::Text::Bold);
	this->uiText.setString("NONE");
}

void Game::initWindow() {
	this->videoMode.height = 720;
	this->videoMode.width = 1280;
	// this->videoMode.desktop
	this->window = new sf::RenderWindow(this->videoMode, "My First Game", sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize);

	// Too high of framesRate may crash window
	this->window->setFramerateLimit(60);
}



void Game::initEnemies()
{
	this->enemy.setPosition(10.f, 10.f); // Set position 
	this->enemy.setSize(sf::Vector2f(100.f, 100.f)); // setSize(sf::Vector2f param) Vector2f(float x, float y);
	this->enemy.setScale(sf::Vector2f(1.0f, 1.0f)); // Scales object
	this->enemy.setFillColor(sf::Color::Red); // Set color 
	this->enemy.setOutlineColor(sf::Color::Black); // Set border color
	this->enemy.setOutlineThickness(2.f); // Set border thickness
}

// Constructor
Game::Game() {
	this->initVariables();
	this->initFonts();
	this->initText();
	this->initWindow();
	this->initEnemies();
}

// Destructor
Game::~Game() {
	delete this->window; // Always remember to delete pointer
}

const bool Game::running() const
{
	return this->window->isOpen();
}

const bool Game::getEndGame() const
{
	return this->endGame;
}

// Functions

/*
* @return void
* 
* spawn enemies and set their colors and position
*	- set random color
*	- set random position
*	- adds enemy to vector
*/
void Game::spawnEnemies()
{
	this->enemy.setPosition(
		static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemy.getSize().x)), // float value of x pos
		static_cast<float>(rand() % static_cast<int>(this->window->getSize().y - this->enemy.getSize().y)) // float value of y pos
	);
	//std::cout << this->enemy.getSize().y;

	/*
	* 
	* Randomize enemy type by color change and scaling 
	* - Add different amount of points for different enemies
	* - Lose more health based on enemies ? 
	* - enemy moves faster?
	* 
	*/ 
	int type = rand() % 10; // range from 0 to 9
	switch (type)
	{
	case(0):
		this->enemy.setFillColor(sf::Color::Red);
		this->enemy.setScale(0.3f, 0.3f);
		break;
	case(1):
	case(2):
	case(3):
		this->enemy.setFillColor(sf::Color::Blue);
		this->enemy.setScale(0.5f, 0.5f);
		break;
	case(4):
	case(5):
	case(6):
	case(7):
	case(8):
	case(9):
		this->enemy.setFillColor(sf::Color::Green);
		this->enemy.setScale(1.0f, 1.0f);
		break;
	default:
		this->enemy.setFillColor(sf::Color::Yellow);
		this->enemy.setScale(1.0f, 1.0f);
		break;
	}

	// spawn enemy (push into vector)
	this->enemies.push_back(this->enemy);
}

/*
* 
* Read window events 
*/
void Game::pollEvents(){
	while (this->window->pollEvent(ev)) { // whenever window get event, we're going to save into ev Event object
		switch (this->ev.type) {
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
/*
* 
* Updates mouse position(Vector2i) relative to window
* @return void
*/
void Game::updateMousePosition()
{

	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow); // mapping mousePos to map it to view 


}
/*
* @return void
* 
* update enemies spawn timer to spawn more enemies if amount of enemies < maxEnemies
*	- move enemy downward
*	- remove enemy at the edge of screen
*/
void Game::updateEnemies()
{

	if (this->enemies.size() < this->maxEnemies) {
		// reset timer to spawn enemey
		if (this->enemySpawnTimer >= this->enemySpawnTimerMax) {
			this->spawnEnemies();
			this->enemySpawnTimer = 0.f;
		}
		else {
			// increment timer
			this->enemySpawnTimer += 1.f;
		}
	}

	// Move enemies
	//for (auto &e : this->enemies) {
	//	if (e.getPosition().y >= this->window->getSize().y || e.getPosition().y <= 0) {
	//		float xpos = static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemy.getSize().x));
	//		e.setPosition(xpos, 10);
	//	}
	//	else {
	//		e.move(0.f, 5.f); // move all enemies down
	//	}
	//}
	// Make your own vector class
	// Moving and updating(removing) enemies 
	for (int i = 0; i < this->enemies.size(); i++)
	{
		bool deleted = false;

		this->enemies[i].move(0.f, 1.f);

		if (this->enemies[i].getPosition().y > this->window->getSize().y)
		{
			this->enemies.erase(this->enemies.begin() + i);
			this->health--;
			std::cout << "Health: " << this->health << "\n";
		}
	}
	// Check if clicked upon
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) 
	{
		if(this->mouseHeld == false) 
		{
			this->mouseHeld = true;
			bool deleted = false;
			//std::cout << this->mousePosWindow.y;
			// If we click and in the bound of enemies, delete enemy
			for (size_t i = 0; i < this->enemies.size() && deleted == false; i++)
			{
				if (this->enemies[i].getGlobalBounds().contains(this->mousePosView))
				{
					// When click on enemy add point accordingly
					if (this->enemies[i].getFillColor() == sf::Color::Red)
					{
						this->points += 10;
					}
					else if (this->enemies[i].getFillColor() == sf::Color::Blue)
					{
						this->points += 5;
					}
					else if (this->enemies[i].getFillColor() == sf::Color::Green)
					{
						this->points += 1;
					}
					std::cout << "Points: " << this->points << "\n";

					// delete enemy
					deleted = true;
					this->enemies.erase(this->enemies.begin() + i);
				}
			}
		}
	}
	else 
	{
		this->mouseHeld = false;
	}
	
}

void Game::updateText()
{
	std::stringstream ss;

	ss << "Points: " << this->points << "\n" 
		<< "Health: " << this->health;

	this->uiText.setString(ss.str()); //stringstream.str() converts stream object to string

	//if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	//{
	//	if (this->mouseHeld == false)
	//	{
	//		this->mouseHeld = true;
	//		if (this->uiText.getGlobalBounds().contains(this->mousePosView))
	//		{
	//			this->uiText.setFillColor(sf::Color::Magenta);
	//		}
	//	}
	//	else
	//	{
	//		this->mouseHeld = false;
	//	}
	//}
}

/*
* 
* Call pollevent function to constantly update window based on events
*/
void Game::update() {
	this->pollEvents(); // press esc to close window
	if (!this->endGame) 
	{
		this->updateMousePosition();

		// Update Text
		this->updateText();

		// Update enemies
		this->updateEnemies();
	}
	// Update mouse position

	// Relative to screen
		// std::cout << "Mouse pos: " << sf::Mouse::getPosition().x << " " << sf::Mouse::getPosition().y << "\n"; // Print mouse position to console

	// Relative to window
		//std::cout << "Mouse pos: " << sf::Mouse::getPosition(*this->window).x 
		//	<< " " << sf::Mouse::getPosition(*this->window).y << "\n";

	// End game 
	if (this->health <= 0) 
	{
		this->endGame = true;
	}
}

/*
* 
* 
* Note:
* - RenderTarget allow us to not be bound to screen and choose where to draw 
* different elements
*/
void Game::renderText(sf::RenderTarget& target) 
{
	target.draw(this->uiText); 
}

/*
* @return void
* 
* render/display enemies
* 
*/
void Game::renderEnemies(sf::RenderTarget& target)
{
	for (auto &e : this->enemies) {
		target.draw(e);
	}
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


	this->window->clear(sf::Color::White); // Clear old frame

	// Draw game objects
		// this->window->draw(this->enemy); // Don't directly draw to window like this
	this->renderEnemies(*this->window); // render/display enemies 

	this->renderText(*this->window);

	this->window->display(); // Tell app that window is done drawing
}

