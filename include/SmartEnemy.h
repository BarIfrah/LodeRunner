#pragma once
#include <SFML/Graphics.hpp>
#include "MovingObject.h"
#include "Enemy.h"
using namespace std;
using namespace sf;

class SmartEnemy :public Enemy
{
public:
	using Enemy::Enemy;
	void addPlayer(Player *player);
	int whereToMove() override;
	float getXdistance() const;
	float getYdistance() const;

private:
	Player* m_player;
};