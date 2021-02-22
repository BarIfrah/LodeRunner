#include <SFML/Graphics.hpp>
#include "Enemy.h"
#include "Player.h"
using namespace std;
using namespace sf;

//----------------------------------------------------------------------------
void Enemy::handleCollision(GameObject& gameObject)
{
    if (&gameObject == this) return;
    // double dispatch
    gameObject.handleCollision(*this);
}
//----------------------------------------------------------------------------
void Enemy::handleCollision(Player& gameObject)
{
    //gameObject.handleCollision(*this);
}
//----------------------------------------------------------------------------
void Enemy::handleCollision(Wall& gameObject)
{
    //ignore
}
//----------------------------------------------------------------------------
void Enemy::handleCollision(Ladder& gameObject)
{
    m_isOnLadder = true;
}
//----------------------------------------------------------------------------
void Enemy::handleCollision(Rope& gameObject)
{
    //ignore
}
//----------------------------------------------------------------------------
void Enemy::resetLadder()
{
    m_isOnLadder = false;
}
//----------------------------------------------------------------------------