#include <SFML/Graphics.hpp>
#include "StaticObject.h"
#include "Wall.h"
#include "Player.h"
#include "Enemy.h"
using namespace std;
using namespace sf;

Wall::Wall(const Wall &other)  : StaticObject(other) {
    m_rec = other.m_rec;
    m_type = other.m_type;
}
//----------------------------------------------------------------------------
bool Wall::shouldIprint() const
{
    if (!m_disappear) return true;
    if (m_clock.getElapsedTime().asSeconds() >= (float)m_timeToAppear)
    {
        return true;
    }
    return false;
}
//----------------------------------------------------------------------------
void Wall::setDisappear()
{
    m_clock.restart();
    m_disappear = true;
}
//----------------------------------------------------------------------------
void Wall::handleCollision(GameObject& gameObject) 
{
    if (&gameObject == this) return;
    // double dispatch
    gameObject.handleCollision(*this);
}
//----------------------------------------------------------------------------
void Wall::handleCollision(Player& gameObject)
{
    //double dispatch
    gameObject.handleCollision(*this);
}
//----------------------------------------------------------------------------
void Wall::handleCollision(Enemy& gameObject)
{
    //double dispatch
    gameObject.handleCollision(*this);
}
//----------------------------------------------------------------------------