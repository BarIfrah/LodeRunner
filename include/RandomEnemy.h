#pragma once
#include <SFML/Graphics.hpp>
#include "MovingObject.h"
#include "Enemy.h"
using namespace std;
using namespace sf;

class RandomEnemy :public Enemy
{
public:
	using Enemy::Enemy;
	//Enemy(char type = '#', sf::Vector2f size = sf::Vector2f(0, 0), sf::Vector2f location = sf::Vector2f(0, 0), Texture* texture = new Texture(), vector <Texture> textures = {}, int speed = 1, int seed = 0);
	int whereToMove() override;

private:

};