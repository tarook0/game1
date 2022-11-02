#pragma once
#include<vector>
#include <sstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include<iostream>
#include<ctime>
/*
Class that act as the game engine.
wrapper class.
*/
class Game
{
private:
	//Variables 
	// window
	sf::RenderWindow* window;
	sf::Event ev;
	sf::VideoMode videoMode;
	
	//Mouse positions
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	//Ressources
	sf::Font font;

	//Text 
	sf::Text uiText;

	//private function
	void initVariables();
	void initWindow();
	void initEnmies();
	void initFonts();
	void initText();
	//Game logic
	bool endGame;
	unsigned points;
	float enemySpawnTimer;
	float enemySpawnTimerMax;
	int maxEnemies;
	bool mouseHeld;
	int health;

	//Game objects
	std::vector<sf::RectangleShape> enemies;
	sf::RectangleShape enemy;


public:
	
	
	//constructors and distructors
	Game();
	virtual ~Game();
	
	
	//Accessors
	const bool running() const;
	const bool getEndGame() const;
	
	//Functions
	void pollEvents();
	void spawnEnemy();
	void render();
	void renderEnmies(sf::RenderTarget& target);
	void renderText(sf::RenderTarget& target);
	void updateMousePositions();
	void updateEnmies();
	void updaetText();
	void update();
	
	
};

