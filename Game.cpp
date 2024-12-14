#include "Game.h"

//Private functions
void Game::initVariables()
{
	this->window = nullptr;

	//Game logic
	this->points = 0;
	this->enemySpawnTimerMax = 1000.f;
	this->enemySpawnTimer = this->enemySpawnTimerMax;
	this->maxEnemies = 5;

}

void Game::initWIndow()
{
	this->videoMode.height = 600;
	this->videoMode.width = 800;

	// Allocazione dinamica di sf::RenderWindow
	this->window = new sf::RenderWindow(this->videoMode, "My first game", sf::Style::Titlebar | sf::Style::Close);

	this->window->setFramerateLimit(60);
}

void Game::InitEnemies()
{
	this->enemy.setPosition(10.f, 10.f);
	this->enemy.setSize(sf::Vector2f(100.f, 100.f));
	this->enemy.setScale(sf::Vector2f(0.5f, 0.5f));
	this->enemy.setFillColor(sf::Color::Cyan);
	this->enemy.setOutlineColor(sf::Color::Green);
	this->enemy.setOutlineThickness(1.f);
}

//Public functions

//Constructors / Destructors
Game::Game()
{
	this->initVariables();
	this->initWIndow();
	this->InitEnemies();
}

Game::~Game()
{
	// Deallocazione della memoria
	delete this->window;
}

const bool Game::running() const 
{
	return this->window->isOpen();
}


void Game::spawnEnemy()
{
	/*
		@return void

		Spawns enemies and sets the color and positions
		- sets a random position
		- sets a random color
		-adds enemy to the vector
	*/

	this->enemy.setPosition(
		static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemy.getSize().x)),
		0.f
	);

	this->enemy.setFillColor(sf::Color::Green);

	this->enemies.push_back(this->enemy);

	//Remove enemies at end of screen
}

void Game::pollEvents()
{
	//Event polling
	while (this->window->pollEvent(this->ev))
	{
		switch (this->ev.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (ev.key.code == sf::Keyboard::Escape)
				this->window->close();
			break;
		}
	}
}

void Game::updateMousePositions()
{
	/*
		@ return void

		Updates  the mouse positions:
		- Mouse positions relative to the window (Vector2i)
	*/

	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
}

void Game::updateEnemies()
{
	/*
		@return void
		
		Updates the enemy spawn timer and spawns enemies
		when the total amount of enemies is smaller than the max.
		Moves the enemies downwords.
		Removes the enemies at the edge of the screen. //TODO
	*/

	//Updating timer for enemy spwaning
	if (this->enemies.size() < this->maxEnemies)
	{
		if (this->enemySpawnTimer >= this->enemySpawnTimerMax)
		{
			//Spwan enemy and reset timer
			this->spawnEnemy();
			this->enemySpawnTimer = 0.f;
		}
		else
			this->enemySpawnTimer += 1.f;
	}

	//Move the enemies
	for (auto &e : this->enemies)
	{
		e.move(0.f, 1.f);
	}
}

//Functions
void Game::update()
{
	this->pollEvents();

	this->updateMousePositions();

	this->updateEnemies();
}

void Game::renderEnemies()
{
	//Rendering all the enemies
	for (auto& e : this->enemies)
	{
		this->window->draw(e);
	}
}

void Game::render()
{
	/*
		@return void

		- clear old frame
		- render objects
		- display frame in window

		Renders the game objects.
	*/
	this->window->clear();

	//Draw game objects
	this->renderEnemies();

	this->window->display();
}
