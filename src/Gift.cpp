#include <SFML/Graphics.hpp>
#include "StaticObject.h"
#include "Wall.h"
#include "Gift.h"
#include "Ladder.h"
#include "Rope.h"
#include "Player.h"
#include "Enemy.h"
using namespace std;
using namespace sf;

//----------------------------------------------------------------------------
void Gift::handleCollision(GameObject& gameObject)
{
    if (&gameObject == this) return;
    // double dispatch
    gameObject.handleCollision(*this);
}
//----------------------------------------------------------------------------
void Gift::handleCollision(Player& gameObject)
{
    m_taken = true;
    gameObject.handleCollision(*this);
}
//----------------------------------------------------------------------------
bool Gift::isTaken() const
{
    return m_taken;
}
//----------------------------------------------------------------------------