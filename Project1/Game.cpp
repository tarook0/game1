#include "Game.h"

//private functions
void Game::initVariables()
{
	this->window = nullptr;
    //Game logic 
    
    this->points = 0;
    this->enemySpawnTimerMax = 10.f;
    this->health = 10.0;
    this->enemySpawnTimer = this->enemySpawnTimerMax;
    this->maxEnemies = 10;
    this->mouseHeld = false;
    this->endGame = false;

}

void Game::initWindow()
{

	this->videoMode.height = 600;
	this->videoMode.width = 800;
	this-> window = new sf::RenderWindow(this->videoMode, "Game1", sf::Style::Titlebar | sf::Style::Close);
    this->window->setFramerateLimit(60);
}

void Game::initEnmies() {
    this->enemy.setPosition(100,100);
    this->enemy.setSize(sf::Vector2f(100.f, 100.f));
    this->enemy.setScale(sf::Vector2f(0.5f, 0.5f));
    this->enemy.setFillColor(sf::Color::Cyan);
    //this->enemy.setOutlineColor(sf::Color::Green);
    //this->enemy.setOutlineThickness(1.f);
    

}

//Constructors / Distructors

Game::Game()
{
	this->initVariables();
	this->initWindow();
    this->initEnmies();
}
Game::~Game()
{
	delete this->window;

}
//Accessors

const bool Game::running()const {
	return this->window->isOpen();
}


const bool Game::getEndGame()const {
    return this->endGame;
}


//Functions
void Game::pollEvents() {

    //Event polling
    while (this->window->pollEvent(this->ev)) {
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
void Game::spawnEnemy() {
    /*
    spawns enemies and set their color an positions:
    -   sets a random positions .
    -   set a random color.
    -   Add enemy to the vector.
    */
    this->enemy.setPosition(
        static_cast<float>(rand() % static_cast<int>(this->window->getSize().x-this->enemy.getSize().x)),0.f);
    this->enemy.setFillColor(sf::Color::Green);
    //Spawn the enemy 

    this->enemies.push_back(this->enemy);
}

void Game::renderEnmies() {
    for (auto& e : this->enemies) {
        this->window->draw(e);
    }

}
void Game::render()
{
    /*
    @return void .
    -   clear frame.
    -   render objects .
    -   display frame in window .
    -   render the game objects .
    */

    this->window->clear();

    //Draw game objects
    this->renderEnmies();
    this->window->display();

}

void Game::update()
{
    this->pollEvents();
    if (this->endGame==false) {


        this->updateMousePositions();

        this->updateEnmies();
    }
    //End game condation
    if (this->health <= 0) {
        this->endGame = true;
    }
}

void Game::updateMousePositions() {

    this->mousePosWindow = sf::Mouse::getPosition(*this->window);
    this->mousePosView= this->window->mapPixelToCoords(this->mousePosWindow);
    /*
    @return void
    update the mouse position:
    -   mouse position relative to window (Vector2f()).
    */

}
void Game::updateEnmies() {
    /*
     @return void 
     
    -   Update the enemy spawn timer and spawns enemies when
        the total amount of enemies is smaller than the maximum 
    -   Moves th enemies downwards.
    -   removes the enemies at the edge of the screen .//todo
    
    */
    //update the timer for enemies sapwing
    if (this->enemies.size() < this->maxEnemies) {
        if (this->enemySpawnTimer >= this->enemySpawnTimerMax) {
            this->spawnEnemy();
            this->enemySpawnTimer = 0.f;
        }
        else
            this->enemySpawnTimer += 1.f;
    }
    //Moving and updateing   enemies 
    for (int i = 0;i < this->enemies.size();i++) {
        bool deleted = false;
        
        this->enemies[i].move(0.f, 5.f);    
        
        //if the enemy is past the bottom of the screen
        if (this->enemies[i].getPosition().y > this->window->getSize().y) {
            this->enemies.erase(this->enemies.begin() + i);
            this->health -= 1;
            std::cout << "Health:" << this->health << "\n";
        }
    
    
    }
    //check if clicked upon

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if (this->mouseHeld==false)
        {
            this->mouseHeld = true;
            bool deleted = false;
            for (size_t i = 0; i < this->enemies.size() && deleted == false; i++)
            {

                if (this->enemies[i].getGlobalBounds().contains(this->mousePosView)) {
                    //Delete the enemy 
                    deleted = true;
                    this->enemies.erase(this->enemies.begin() + i);
                    //gain points
                    this->points += 1;
                    std::cout << "point:" << this->points << '\n';

                }
            }
        }
    }
    else {
        this->mouseHeld = false;
    }
}
