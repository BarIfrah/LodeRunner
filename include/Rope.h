#pragma once
#include <SFML/Graphics.hpp>
#include "StaticObject.h"
using namespace std;
using namespace sf;

class Rope :public StaticObject
{
public:
	using StaticObject::StaticObject;
	void handleCollision(GameObject& gameObject) override;
	void handleCollision(Player& gameObject) override;
	void handleCollision(Enemy& gameObject) override;
	void handleCollision(Wall& gameObject) override {};
	void handleCollision(Coin& gameObject) override {};
	void handleCollision(Ladder& gameObject) override {};
	void handleCollision(Rope& gameObject) override {};
    void handleCollision(Gift& gameObject) override {};
private:
};