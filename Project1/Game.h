#pragma once
#include<vector>
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
	//private function
	void initVariables();
	void initWindow();
	void initEnmies();

	
	//Game logic
	unsigned points;
	float enemySpawnTimer;
	float enemySpawnTimerMax;
	int maxEnemies;
	bool mouseHeld;


	//Game objects
	std::vector<sf::RectangleShape> enemies;
	sf::RectangleShape enemy;


public:
	
	
	//constructors and distructors
	Game();
	virtual ~Game();
	
	
	//Accessors
	const bool running() const;
	
	
	//Functions
	void pollEvents();
	void render();
	void renderEnmies();
	void updateMousePositions();
	void updateEnmies();
	void spawnEnemy();
	void update();
};

