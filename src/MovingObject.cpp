#include <SFML/Graphics.hpp>
#include "MovingObject.h"
#include "Controller.h"
#include <vector>
using namespace sf;
using namespace std;
//----------------------------------------------------------------------------
MovingObject::MovingObject(char type, sf::Vector2f size, sf::Vector2f location,
                           Texture* texture, const vector <Texture*>& textures, int speed) :GameObject(type, size, location, texture)
{
    m_textures = textures;
    m_speed = speed;
}
//----------------------------------------------------------------------------
void MovingObject::move(Controller *controller, Time time)
{
    if (m_isTrapped) return;
    float criticalMovement = time.asSeconds();
    int direction = this->whereToMove()/*, can_move = 0*/;

    if (!canMove(direction, controller, criticalMovement) && canMove(direction, controller, 0.4/m_speed)) criticalMovement = 0.4/m_speed;
    if (canMove(direction, controller, criticalMovement))
        switch (direction)
        {
            case Up: m_rec.move(0, (-m_speed * criticalMovement)); break;
            case Down: m_rec.move(0, (m_speed * criticalMovement)); break;
            case Left: m_rec.move((-m_speed * criticalMovement), 0); m_rec.setScale(-1, 1); break;
            case Right: m_rec.move((m_speed * criticalMovement), 0); m_rec.setScale(1, 1); break;
            case Still: m_rec.setTexture(m_textures[m_textures.size() - 1]); break;
            default: break;
        }
    if (direction != Still) nextTexture();
    fall(controller);
}
//----------------------------------------------------------------------------
bool MovingObject::canMove(int direction, Controller* controller, float criticalMovement) const
{
    RectangleShape temp = m_rec;
    switch (direction)
    {
        case Up: temp.move(0, (-m_speed * criticalMovement)); break;
        case Down: temp.move(0, (m_speed * criticalMovement)); break;
        case Left: temp.move((-m_speed * criticalMovement), 0); break;
        case Right: temp.move((m_speed * criticalMovement), 0); break;
        case Still: return true;
        default: break;
    }
    for (int i = 0; i < controller->getStaticSize(); i++) {
        if (controller->getStaticObject(i)->getType() == wall && controller->getStaticObject(i)->collide_with(temp))
        {
            return false;
        }
    }
    return true;
}
//----------------------------------------------------------------------------
void MovingObject::nextTexture()
{
    m_state++;
    if (m_state >= m_textures.size()-2) m_state = 0;
    this->setTexture(m_textures[m_state]);
}
//----------------------------------------------------------------------------
void MovingObject::fall(Controller* controller)
{
    while (true)
    {
        if (controller->checkTrap(*this)) return;
        RectangleShape temp = m_rec;
        temp.setPosition(temp.getPosition().x, temp.getPosition().y + 1);
        for (int i = 0; i < controller->getStaticSize(); i++) {
            if (controller->getStaticObject(i)->getType() == coin || controller->getStaticObject(i)->getType() == gift) continue;
            if (controller->getStaticObject(i)->collide_with(m_rec))
            {
                if (controller->getStaticObject(i)->getType() != rope) return;
                //we're on a rope
                RectangleShape Ropeline(sf::Vector2f(controller->getStaticObject(i)->getRectangle().getSize().x, 1));
                RectangleShape Playerline(sf::Vector2f(m_rec.getSize().x, 1));
                Ropeline.setPosition(controller->getStaticObject(i)->getRectangle().getPosition());
                Playerline.setPosition(m_rec.getPosition());
                if (Playerline.getGlobalBounds().intersects(Ropeline.getGlobalBounds()))
                {
                    m_rec.setTexture(m_textures[m_textures.size()-2]);
                    return;
                }
            }
            if (((controller->getStaticObject(i)->getType() == wall) || (controller->getStaticObject(i)->getType() == ladder)) && controller->getStaticObject(i)->collide_with(temp))
                return;
        }
        m_rec.move(0, 1);
    }
}
