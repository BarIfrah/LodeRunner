#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include "StaticObject.h"
using namespace std;
using namespace sf;

class Coin :public StaticObject
{
public:
    using StaticObject::StaticObject;
    bool isTaken() const;
    
    void handleCollision(GameObject& gameObject) override;
    void handleCollision(Player& gameObject) override;
    void handleCollision(Enemy& gameObject) override {};
    void handleCollision(Wall& gameObject) override {};
    void handleCollision(Coin& gameObject) override {};
    void handleCollision(Ladder& gameObject) override {};
    void handleCollision(Rope& gameObject) override {};
    void handleCollision(Gift& gameObject) override {};

private:
    Music* m_sound = new Music;
	bool m_taken = false;
};