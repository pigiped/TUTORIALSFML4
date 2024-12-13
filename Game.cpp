#include "Game.h"

//Private functions
void Game::initVariables()
{
	this->window = nullptr;
}

void Game::initWIndow()
{
	this->videoMode.height = 600;
	this->videoMode.width = 800;

	this->window = new sf::RenderWindow(this->videoMode, "My first game", sf::Style::Titlebar | sf::Style::Close);
}

//Constructors / Destructors
Game::Game()
{
	this->initVariables();
	this->initWIndow();  
}

Game::~Game()
{
	delete this->window;
}

const bool Game::running() const 
{
	return this->window->isOpen();
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

//Functions
void Game::update()
{
	this->pollEvents();
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
	this->window->clear(sf::Color::Blue);

	//Draw game objects

	this->window->display();
}
