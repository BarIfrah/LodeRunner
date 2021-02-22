#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "Enemy.h"
#include "Player.h"
#include "SmartEnemy.h"
using namespace std;
using namespace sf;
//----------------------------------------------------------------------------
void SmartEnemy::addPlayer(Player* playerObject)
{
    m_player = playerObject;
}
//----------------------------------------------------------------------------
int SmartEnemy::whereToMove()
{
    int Ydistance = 0, Xdistance;
    if (m_isOnLadder)
    {
        Ydistance = (int)getYdistance();
    }
    Xdistance = (int)getXdistance();
    if (abs(Xdistance) > abs(Ydistance))
    {
        if (m_rec.getPosition().x < m_player->getRectangle().getPosition().x)
            return Right;
        else return Left;
    }
    if (m_rec.getPosition().y < m_player->getRectangle().getPosition().y)
        return Down;
    else return Up;
}
//----------------------------------------------------------------------------
float SmartEnemy::getXdistance() const
{
    return m_rec.getPosition().x - m_player->getRectangle().getPosition().x;
}
//----------------------------------------------------------------------------
float SmartEnemy::getYdistance() const 
{
    return m_rec.getPosition().y - m_player->getRectangle().getPosition().y;
}
//----------------------------------------------------------------------------