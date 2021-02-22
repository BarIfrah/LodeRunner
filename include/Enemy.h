#pragma once
#include <SFML/Graphics.hpp>
#include "MovingObject.h"
using namespace std;
using namespace sf;

class Enemy :public MovingObject
{
public:
	using MovingObject::MovingObject;
	void resetLadder();
	void handleCollision(GameObject& gameObject) override;
	void handleCollision(Player& gameObject) override;
	void handleCollision(Enemy& gameObject) override {};
	void handleCollision(Wall& gameObject) override;
	void handleCollision(Coin& gameObject) override {};
	void handleCollision(Ladder& gameObject) override;
	void handleCollision(Rope& gameObject) override;
	void handleCollision(Gift& gameObject) override {};

protected:
	bool m_isOnLadder = false;
};