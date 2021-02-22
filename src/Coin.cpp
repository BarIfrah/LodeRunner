#include <SFML/Graphics.hpp>
#include "StaticObject.h"
#include "Wall.h"
#include "Coin.h"
#include "Ladder.h"
#include "Rope.h"
#include "Player.h"
#include "Enemy.h"
using namespace std;
using namespace sf;

//----------------------------------------------------------------------------
void Coin::handleCollision(GameObject& gameObject) 
{
    if (&gameObject == this) return;
    // double dispatch
    gameObject.handleCollision(*this);
}
//----------------------------------------------------------------------------
void Coin::handleCollision(Player& gameObject) 
{
    m_sound->openFromFile("coin_cellect.ogg");
    m_sound->setLoop(false);
    m_sound->setVolume(8);
    m_sound->play();
    m_taken = true;
    gameObject.handleCollision(*this);
}
//----------------------------------------------------------------------------
bool Coin::isTaken() const
{
    return m_taken;
}
//----------------------------------------------------------------------------