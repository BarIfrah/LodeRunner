#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "StaticObject.h"
using namespace std;
using namespace sf;

class Wall :public StaticObject
{
public:
	using StaticObject::StaticObject;
	Wall(const Wall& other);
	bool shouldIprint() const;
	void setDisappear();
	void handleCollision(GameObject& gameObject) override;
	void handleCollision(Player& gameObject) override;
	void handleCollision(Enemy& gameObject) override;
	void handleCollision(Wall& gameObject) override {};
	void handleCollision(Coin& gameObject) override {};
	void handleCollision(Ladder& gameObject) override {};
	void handleCollision(Rope& gameObject) override {};
    void handleCollision(Gift& gameObject) override {};

private:
	bool m_disappear = false;
	Clock m_clock;
	int m_timeToAppear = 5;
};