#include "Game.h"

//private functions
void Game::initVariables()
{
	this->window = nullptr;
    //Game logic 
    
    this->points = 0;
    this->enemySpawnTimerMax = 10.f;
    this->health = 20.0;
    this->enemySpawnTimer = this->enemySpawnTimerMax;
    this->maxEnemies = 4;
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
    this->enemy.setPosition(10,10);
    this->enemy.setSize(sf::Vector2f(10.f, 10.f));
    this->enemy.setFillColor(sf::Color::Cyan);
    //this->enemy.setOutlineColor(sf::Color::Green);
    //this->enemy.setOutlineThickness(1.f);
    

}
void Game::initFonts() {
    if (this->font.loadFromFile("Fonts/Dosis-Light.ttf")) {
        std::cout << "ERROR::Game::INITFaild:: Load Fonts!" << "\n";
    }
}
void Game::initText() {
    this->uiText.setFont(this->font);
    this->uiText.setCharacterSize(20);
    this->uiText.setString("NON");
    this->uiText.setFillColor(sf::Color::Red);
}

//Constructors / Distructors

Game::Game()
{
	this->initVariables();
	this->initWindow();
    this->initText();
    this->initFonts();
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
    spawns enemies and set their types colors ,spawn them at random  positions :
    -   sets a random positions .
    -   set a random color.
    -   Add enemy to the vector.
    */
    this->enemy.setPosition(
        static_cast<float>(rand() % static_cast<int>(this->window->getSize().x-this->enemy.getSize().x)),0.f);
   //Randomize enemy type 
    int type = rand() % 5;
    switch (type)
    {
    case 0:
        this->enemy.setFillColor(sf::Color::Magenta);
        this->enemy.setSize(sf::Vector2f(10.f, 10.f));
        break;
    case 1:
        this->enemy.setFillColor(sf::Color::Blue);
        this->enemy.setSize(sf::Vector2f(30.f, 30.f));
        break;
    case 2:
        this->enemy.setFillColor(sf::Color::Green);
        this->enemy.setSize(sf::Vector2f(50.f, 50.f));
        break;
    case 3:
        this->enemy.setFillColor(sf::Color::Red);
        this->enemy.setSize(sf::Vector2f(70.f, 70.f));
        break;
    case 4:
        this->enemy.setFillColor(sf::Color::White);
        this->enemy.setSize(sf::Vector2f(100.f, 100.f));
        break;
    default:
        this->enemy.setFillColor(sf::Color::Yellow);
        this->enemy.setSize(sf::Vector2f(100.f, 100.f));
        break;
    }
    //Spawn the enemy 

    this->enemies.push_back(this->enemy);
}

void Game::renderEnmies(sf::RenderTarget& target) {
    for (auto& e : this->enemies) {
        target.draw(e);
    }

}
void Game::renderText(sf::RenderTarget& target) 
{
    target.draw(this->uiText);
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
    this->renderEnmies(*this->window);
    this->renderText(*this->window);
    this->window->display();

}


void Game::update()
{
    this->pollEvents();
    if (this->endGame==false) {

        this->updateMousePositions();

        this->updaetText();

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
                    //gain points
                    if(this->enemies[i].getFillColor()== sf::Color::Magenta)
                    this->points += 10;
                    else if (this->enemies[i].getFillColor() == sf::Color::Blue)
                        this->points += 7;
                    else if (this->enemies[i].getFillColor() == sf::Color::Green)
                        this->points += 5;
                    else if (this->enemies[i].getFillColor() == sf::Color::Red)
                        this->points += 3;
                    else if (this->enemies[i].getFillColor() == sf::Color::Yellow)
                        this->points += 1;
                    
                    std::cout << "point:" << this->points << '\n';
                    //Delete the enemy 
                    deleted = true;
                    this->enemies.erase(this->enemies.begin() + i);

                }
            }
        }
    }
    else {
        this->mouseHeld = false;
    }
}
void Game::updaetText() {
    std::stringstream ss;
    ss << "Points:" << this->points<<'\n';
    ss << "Health:" << this->health << '\n';

    this->uiText.setString(ss.str());
}