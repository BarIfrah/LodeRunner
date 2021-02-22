#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "MovingObject.h"
using namespace std;
using namespace sf;

class Player :public MovingObject
{
public:
	using MovingObject::MovingObject;
	int whereToMove() override;
	Player(const Player  &other) ;
	int getLife() const;
	int getScore() const;
    int getCoinsCollected() const;
	bool isDead();
	void setLife(int life);
	void reduceLife();
	void addScore(int score);
	void addLife();
	bool didTakeGift();
	void setLevel(int level);

	void handleCollision(GameObject& gameObject) override;
	void handleCollision(Player& gameObject) override {};
	void handleCollision(Enemy& gameObject) override;
	void handleCollision(Wall& gameObject) override {};
	void handleCollision(Coin& gameObject) override;
	void handleCollision(Ladder& gameObject) override;
	void handleCollision(Rope& gameObject) override;
    void handleCollision(Gift& gameObject) override;

private:
	int m_life = 3, m_score = 0, m_coinsCollected = 0, m_level = 1;
	bool m_died = false;
	bool m_didTakeGift = false;
};