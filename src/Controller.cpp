#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <string>
#include <windows.h>
#include "Controller.h"
#include "Board.h"
#include "Coin.h"
#include "Wall.h"
#include "Enemy.h"
#include "Ladder.h"
#include "Rope.h"
#include "Gift.h"
#include "macros.h"
#include "Menu.h"
#include "RandomEnemy.h"
#include "SmartEnemy.h"
#include "PatrolEnemy.h"
#include "StatsBoard.h"
#include "Player.h"
#include <experimental/vector>
#include <memory>
using namespace std;
using namespace sf;
//----------------------------------------------------------------------------
Controller::Controller(string file_name) : m_window(sf::VideoMode(Window_width, Window_height), "Lode Runner")
{
    m_playerIndex = 0;
    m_player = nullptr ; // init to null. will be overridden later
    ::ShowWindow(m_window.getSystemHandle(), SW_MAXIMIZE);
    m_window.setFramerateLimit(60);
	m_board = Board(file_name);
	m_levelTime = m_board.getTime(m_level-1);
	if (m_levelTime == -1) m_unlimitedTime = true;
	createObjectDataStructure();
	m_totalLevels = m_board.getLevels();

	auto texture = new Texture;		//texture for the background
	texture->loadFromFile("background.jfif");
	m_background = RectangleShape(Vector2f(m_window.getSize().x, m_window.getSize().y));
	m_background.setTexture(texture);

	m_stats = StatsBoard();
}
//----------------------------------------------------------------------------
void Controller::run() {
	Menu menu(m_background);
	menu.showMenu(m_window);
	m_window.clear();
	m_music = getMusic();
	m_music->play();
	sf::Time deltaTime;
	while (m_window.isOpen())
	{
		deltaTime = m_clock.restart();
		draw();
		handleEvents();
		updateGameObjects(deltaTime);
	}
}
//----------------------------------------------------------------------------
void Controller::draw()
{
	m_window.clear();
	m_window.draw(m_background);
	for (int i = 0; i < m_staticObjects.size(); i++) {
	    m_staticObjects[i]->Draw(m_window);
	}
    for (int i = 0; i < m_movingObjects.size(); i++) {
        m_movingObjects[i]->Draw(m_window);
    }
	m_stats.Draw(m_window);
	m_window.display();
}
//----------------------------------------------------------------------------
void Controller::handleEvents()
{
	for (auto event = sf::Event{}; m_window.pollEvent(event); )
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			m_window.close();
			break;

		case sf::Event::KeyPressed:
			if (event.key.code == sf::Keyboard::Escape)
			{
				m_window.close();
				break;
			}
			if (event.key.code == sf::Keyboard::X)
			{
				dig(true);
			}
			if (event.key.code == sf::Keyboard::Z)
			{
				dig(false);
			}
			break;
		}
	}
}
//----------------------------------------------------------------------------
void Controller::updateGameObjects(Time time)
{
	for (int i = 0; i < m_deletedWalls.size(); i++)
	{
		if (dynamic_cast<Wall*>(m_deletedWalls[i].get()))
		{
			if (dynamic_cast<Wall*>(m_deletedWalls[i].get())->shouldIprint())
			{
				freeTrapped(*m_deletedWalls[i]);
				m_staticObjects.push_back(move(m_deletedWalls[i]));
				m_deletedWalls.erase(m_deletedWalls.begin() + i);
			}
		}
	}

	for (int i = 0; i < m_movingObjects.size(); i++)
	{
	    m_movingObjects[i]->move(this, time);
		handleCollisions(*m_movingObjects[i]);
	}
	if (m_player->didTakeGift()) tookGift();

	experimental::erase_if(m_staticObjects, [](const auto& coin) {return ((dynamic_cast<Coin*>(coin.get())) && (dynamic_cast<Coin*>(coin.get()))->isTaken()); });
    experimental::erase_if(m_staticObjects, [](const auto& gift) {return ((dynamic_cast<Gift*>(gift.get())) && (dynamic_cast<Gift*>(gift.get()))->isTaken()); });
	string timeLeft = (m_unlimitedTime) ? string("Unlimited") : (to_string(int(m_levelTime -= time.asSeconds())));
	m_stats.Update(m_player, m_level, timeLeft);
	if (m_stats.isOver()) GameOver();
	m_score = m_player->getScore();
    int collectedCoins =  m_player->getCoinsCollected();

    if (m_levelCoins - collectedCoins == 0) {
        m_levelCoins = 0;
		if (m_totalLevels == m_level++) {
			GameOver();
			return;
		}
		m_score += 50;
		m_unlimitedTime = false;
		m_deletedWalls.clear();
        resetLevel();
		m_player->setLevel(m_level);
		return;
    }

	if (int(m_levelTime) == 0)
	{
		m_player->reduceLife();
		resetLevel();
		return;
	}
	if (m_player->isDead()) resetLevel();
}
//----------------------------------------------------------------------------
Music* Controller::getMusic()
{
	auto music = new Music;
	music->openFromFile("soundtrack.ogg");
	music->setLoop(true);
	music->setVolume(8);
	return music;
}
//----------------------------------------------------------------------------
void Controller::handleCollisions(MovingObject& gameObject)
{
	if (dynamic_cast<Enemy*>(&gameObject))
		dynamic_cast<Enemy*>(&gameObject)->resetLadder();
	for (auto& unmovable : m_staticObjects)
	{
		if (gameObject.collide_with(unmovable->getRectangle()))
		{
			gameObject.handleCollision(*unmovable);
		}
	}

	for (auto& movable : m_movingObjects)
	{
		if (gameObject.collide_with(movable->getRectangle()))
		{
			gameObject.handleCollision(*movable);
		}
	}
}
//----------------------------------------------------------------------------
bool Controller::checkTrap(MovingObject& gameObject)
{
	if ((&gameObject) == m_player) return false;	//player shoud fall through
	for (auto& deletedWall : m_deletedWalls)
	{
		if (gameObject.collide_with(deletedWall->getRectangle()))
		{
			gameObject.setTrapped();
			return true;
		}
	}
	return false;
}
//----------------------------------------------------------------------------
void Controller::freeTrapped(GameObject& wallToCheck)
{
	for (auto& movable : m_movingObjects)
	{
		if (wallToCheck.collide_with(movable->getRectangle()))
		{
			dynamic_cast<MovingObject*>(movable.get())->setFree();
		}
	}
}
//----------------------------------------------------------------------------
void Controller::resetLevel()
{
	int player_life = m_player->getLife();
    m_levelCoins = 0;
	createObjectDataStructure();
	m_player->addScore(m_score);
	m_levelTime = m_board.getTime(m_level-1);
	if (m_levelTime == -1) 	m_unlimitedTime = true;
	m_player->setLife(player_life);
}
//----------------------------------------------------------------------------
void Controller::createObjectDataStructure()
{
	createTextureVectors();
	m_staticObjects.clear();
	m_movingObjects.clear();
	bool playerExist = false;
	Texture* walltexture = buildTexture("wall.png");
	Texture* cointexture = buildTexture("coin.png");
	Texture* laddertexture = buildTexture("ladder.png");
	Texture* ropetexture = buildTexture("rope.png");
	Texture* giftTexture = buildTexture("gift.png");

	int cols = m_board.getCols(m_level-1), rows = m_board.getRows(m_level-1);
	char charFromFile;
	auto size = sf::Vector2f(Board_Width / float(cols), Board_Height / float(rows));
	for (int i = 0; i < rows; i++)
	{
		vector <char> currentLine;
		for (int j = 0; j < cols; j++)
		{
			charFromFile = m_board.getType((m_level-1), i, j);	//get the \n
			switch (charFromFile)
			{
				case player:
				{
					if (playerExist) continue;
					playerExist = true;
					m_playerIndex = m_movingObjects.size();
					m_movingObjects.push_back(make_unique<Player>(player, Vector2f(size.y - 1, size.y - 1),
						Vector2f(STARTING_X + (float(j) * (Board_Width / float(cols))),
							STARTING_Y + (float(i) * (Board_Height / float(rows)))), m_Playertexture[0], m_Playertexture, PlayerSpeed));
					break;
				}

				case enemy:
				{
					switch (((m_movingObjects.size()^2) *5) %3 )
					{
					case 0: m_movingObjects.push_back(make_unique<RandomEnemy>(enemy, Vector2f(size.y - 1, size.y - 1),
						Vector2f(STARTING_X + (float(j) * (Board_Width / float(cols))),
							STARTING_Y + (float(i) * (Board_Height / float(rows)))), m_Renemytexture[0], m_Renemytexture, EnemySpeed));
						break;
					case 1: m_movingObjects.push_back(make_unique<SmartEnemy>(enemy, Vector2f(size.y - 1, size.y - 1),
						Vector2f(STARTING_X + (float(j) * (Board_Width / float(cols))),
							STARTING_Y + (float(i) * (Board_Height / float(rows)))), m_Senemytexture[0], m_Senemytexture, EnemySpeed));
						break;
					case 2: m_movingObjects.push_back(make_unique<PatrolEnemy>(enemy, Vector2f(size.y - 1, size.y - 1),
						Vector2f(STARTING_X + (float(j) * (Board_Width / float(cols))),
							STARTING_Y + (float(i) * (Board_Height / float(rows)))), m_Penemytexture[0], m_Penemytexture, EnemySpeed, patrolRadius));
						break;
					}
					break;
				}

				case wall:
				{
					m_staticObjects.push_back(make_unique<Wall>(wall, size,
						Vector2f(STARTING_X + (float(j) * (Board_Width / float(cols))),
							STARTING_Y + (float(i) * (Board_Height / float(rows)))), walltexture));
					break;
				}

				case coin:
				{
				    m_levelCoins++;
					m_staticObjects.push_back(make_unique<Coin>(coin, Vector2f(size.x / 2, size.y / 2),
						Vector2f(STARTING_X + (float(j) * (Board_Width / float(cols))),
							STARTING_Y + (float(i) * (Board_Height / float(rows)))), cointexture));
					break;
				}
				case ladder:
				{
					m_staticObjects.push_back(make_unique<Ladder>(ladder, size,
						Vector2f(STARTING_X + (float(j) * (Board_Width / float(cols))),
							STARTING_Y + (float(i) * (Board_Height / float(rows)))), laddertexture));
					break;
				}
				case rope:
				{
					m_staticObjects.push_back(make_unique<Rope>(rope, size,
						Vector2f(STARTING_X + (float(j) * (Board_Width / float(cols))),
							STARTING_Y + (float(i) * (Board_Height / float(rows)))), ropetexture));
					break;
				}
                case gift:
                {
                    m_staticObjects.push_back(make_unique<Gift>(gift, Vector2f(size.x / 2, size.y / 2),
                                                                Vector2f(STARTING_X + (float(j) * (Board_Width / float(cols))),
                                                                         STARTING_Y + (float(i) * (Board_Height / float(rows)))), giftTexture));
                    break;
                }
			    default: break;
			}
			currentLine.push_back(charFromFile);
		}
	}
	m_player = dynamic_cast <Player*>(m_movingObjects[m_playerIndex].get());
	for (auto& movable : m_movingObjects)
	{
		if (dynamic_cast <SmartEnemy*>(movable.get()))
		{
			dynamic_cast <SmartEnemy*>(movable.get())->addPlayer(m_player);
		}
	}
}
//----------------------------------------------------------------------------
vector <Texture*> Controller::buildTextures(vector<string> names)
{
	vector <Texture*> textures;
	auto* tempTexture = new Texture();
	for (int i = 0; i < names.size(); i++)
	{
		tempTexture->loadFromFile(names[i]);
		textures.push_back(tempTexture);
		tempTexture = new Texture();
	}
	return textures;
}
//----------------------------------------------------------------------------
Texture* Controller::buildTexture(const string &name)
{
	auto texture = new Texture;
	texture->loadFromFile(name);
	return texture;
}
//----------------------------------------------------------------------------
GameObject* Controller::getStaticObject(int index) const
{
	return m_staticObjects[index].get();
}
//----------------------------------------------------------------------------
int Controller::getStaticSize() const
{
	return int(m_staticObjects.size());
}
//----------------------------------------------------------------------------
void Controller::GameOver() 
{
	RectangleShape gameover = RectangleShape(Vector2f(1000, 800));
	gameover.setPosition(Vector2f(250, 100));
	auto* texture = new Texture();
	texture->loadFromFile("gameover.png");
	gameover.setTexture(texture);
	while (m_window.isOpen() && m_clock.getElapsedTime().asSeconds() < endScreenTime)
	{
		m_window.clear();
		m_window.draw(gameover);
		m_window.display();
		if (auto event = sf::Event{}; m_window.waitEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				m_window.close();
				break;
			}
		}
	}
	m_level = 1;
	m_score = 0;
	m_levelCoins = 0;
	m_levelTime = m_board.getTime(m_level - 1);
	m_music->pause();
	m_staticObjects.clear();
	m_movingObjects.clear();
	m_deletedWalls.clear();
	createObjectDataStructure();
	m_player->setLevel(m_level);
	run();
}
//----------------------------------------------------------------------------
void Controller::tookGift()
{
	srand(time(nullptr));
	switch (rand() % 4)
	{
	case 0:
		m_player->addScore(20);
		break;
	case 1:
		m_player->addLife();
		break;
	case 2:
		if (m_levelTime != -1) m_levelTime += 10;
		else m_player->addScore(20);
		break;
	case 3:
		createEnemy();
		break;
	default: break;
	}
}
//----------------------------------------------------------------------------
void Controller::createEnemy()
{
	int cols = m_board.getCols(m_level - 1), rows = m_board.getRows(m_level - 1), row, col;
	m_board.getBlank(m_level, row, col);
	auto size = sf::Vector2f(Board_Width / float(cols), Board_Height / float(rows));

	m_movingObjects.push_back(make_unique<RandomEnemy>(enemy, Vector2f(size.y - 1, size.y - 1),
		Vector2f(STARTING_X + (float(col) * (Board_Width / float(cols))),
			STARTING_Y + (float(row) * (Board_Height / float(rows)))), m_Renemytexture[0], m_Renemytexture, EnemySpeed));
}
//----------------------------------------------------------------------------
void Controller::dig(bool direction)
{
	Vector2f player_location = backToBasic(m_player->getRectangle().getPosition());
	player_location.y++;
	if(direction) player_location.x++;
	else player_location.x--;

	for (int i = 0; i < m_staticObjects.size(); i ++)
	{
		if (dynamic_cast<Wall*>(m_staticObjects[i].get()))
		{
			if ((backToBasic(dynamic_cast<Wall*>(m_staticObjects[i].get())->getRectangle().getPosition())) == player_location)
			{
				dynamic_cast<Wall*>(m_staticObjects[i].get())->setDisappear();
				m_deletedWalls.push_back(move(m_staticObjects[i]));
				m_staticObjects.erase(m_staticObjects.begin() + i);
				return;
			}
		}
	}
}
//----------------------------------------------------------------------------
Vector2f Controller::backToBasic(Vector2f location)
{
	int cols = m_board.getCols(m_level - 1), rows = m_board.getRows(m_level - 1);
	Vector2f temp;
	temp.x = int((location.x / (Board_Width / float(cols))) - STARTING_X);
	temp.y = int((location.y / (Board_Width / float(rows))) - STARTING_Y);
	return temp;
}
//----------------------------------------------------------------------------
void Controller::createTextureVectors()
{
	m_Playertexture.clear();
	m_Senemytexture.clear();
	m_Penemytexture.clear();
	m_Renemytexture.clear();
	
	vector<string> names;
	names.emplace_back("moving1.png");
	names.emplace_back("moving2.png");
	names.emplace_back("moving3.png");
	names.emplace_back("moving3.png");
	names.emplace_back("moving2.png");
	names.emplace_back("moving1.png");
	names.emplace_back("rope_ang.png");
	names.emplace_back("ang.png");
	m_Playertexture = buildTextures(names);

	names.clear();
	names.emplace_back("azula.png");
	names.emplace_back("azula2.png");
	names.emplace_back("azula3.png");
	names.emplace_back("azula2.png");
	names.emplace_back("azula.png");
	names.emplace_back("azula.png");
	m_Senemytexture = buildTextures(names);

	names.clear();
	names.emplace_back("zuko.png");
	names.emplace_back("zuko.png");
	names.emplace_back("zuko.png");
	m_Renemytexture = buildTextures(names);

	names.clear();
	names.emplace_back("tylee.png");
	names.emplace_back("tylee2.png");
	names.emplace_back("tylee3.png");
	names.emplace_back("tylee4.png");
	names.emplace_back("tylee3.png");
	names.emplace_back("tylee2.png");
	names.emplace_back("tylee.png");
	names.emplace_back("tylee.png");
	m_Penemytexture = buildTextures(names);
}