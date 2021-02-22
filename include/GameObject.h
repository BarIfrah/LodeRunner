#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "macros.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <string>
using namespace sf;

class Controller;
class MovingObject;
class StaticObject;
class Player;
class Enemy;
class Rope;
class Ladder;
class Coin;
class Wall;
class Gift;

class GameObject
{
public:
	explicit GameObject(char type = '#', sf::Vector2f size = sf::Vector2f(0, 0), sf::Vector2f location = sf::Vector2f(0, 0), Texture *texture = new Texture());
	RectangleShape getRectangle();
	void setTexture(Texture *texture);
	char getType() const;
	void Draw(sf::RenderWindow& window);
	bool collide_with(const RectangleShape &other);
	virtual ~GameObject() = default;

	virtual void handleCollision(GameObject& gameObject) = 0;
	virtual void handleCollision(Player& gameObject) = 0;
	virtual void handleCollision(Enemy& gameObject) = 0;
	virtual void handleCollision(Wall& gameObject) = 0;
	virtual void handleCollision(Coin& gameObject) = 0;
	virtual void handleCollision(Ladder& gameObject) = 0 ;
	virtual void handleCollision(Rope& gameObject) = 0;
	virtual void handleCollision(Gift& gameObject) = 0;

protected:
	RectangleShape m_rec;
	char m_type;
};