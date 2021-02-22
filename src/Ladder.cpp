#include <SFML/Graphics.hpp>
#include "Ladder.h"
#include "Enemy.h"
//----------------------------------------------------------------------------
void Ladder::handleCollision(GameObject& gameObject)
{
    if (&gameObject == this) return;
    // double dispatch
    gameObject.handleCollision(*this);
}
//----------------------------------------------------------------------------
void Ladder::handleCollision(Player& gameObject)
{
    //double dispatch
    //gameObject.handleCollision(*this);
}
//----------------------------------------------------------------------------
void Ladder::handleCollision(Enemy& gameObject)
{
    //double dispatch
    gameObject.handleCollision(*this);
}
//----------------------------------------------------------------------------