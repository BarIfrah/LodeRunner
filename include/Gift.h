#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "StaticObject.h"
using namespace std;
using namespace sf;

class Gift :public StaticObject
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
    bool m_taken = false;
};