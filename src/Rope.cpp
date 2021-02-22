#include "Rope.h"
using namespace std;
using namespace sf;
//----------------------------------------------------------------------------
void Rope::handleCollision(GameObject& gameObject)
{
    if (&gameObject == this) return;
    // double dispatch
    gameObject.handleCollision(*this);
}
//----------------------------------------------------------------------------
void Rope::handleCollision(Player& gameObject)
{
    //double dispatch
    //gameObject.handleCollision(*this);
}
//----------------------------------------------------------------------------
void Rope::handleCollision(Enemy& gameObject)
{
    //double dispatch
    //gameObject.handleCollision(*this);
}
//----------------------------------------------------------------------------