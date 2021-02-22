#pragma once
#include <SFML/Graphics.hpp>
#include "MovingObject.h"
#include "Enemy.h"
using namespace std;
using namespace sf;

class PatrolEnemy :public Enemy
{
public:
	explicit PatrolEnemy(char type = '#', sf::Vector2f size = sf::Vector2f(0, 0), sf::Vector2f location = sf::Vector2f(0, 0), Texture* texture = new Texture(), const vector <Texture*> & textures = {}, int speed = 1, int radius = 0);
	int whereToMove() override;

private:
	int m_patrolRadius = 5, m_counter = 0;
	bool m_direction = false;
};