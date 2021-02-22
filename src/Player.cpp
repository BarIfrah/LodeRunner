#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Player.h"
using namespace std;
using namespace sf;
//----------------------------------------------------------------------------
namespace
{
    sf::Vector2f dirFromKey()
    {
        static const
            std::initializer_list<std::pair<sf::Keyboard::Key, sf::Vector2f>>
            keyToVectorMapping =
        {
            { sf::Keyboard::Right , {Right,0} },
            { sf::Keyboard::Left , {Left,0} },
            { sf::Keyboard::Up   , {Up,0} },
            { sf::Keyboard::Down , {Down,0} },
        };

        for (const auto& pair : keyToVectorMapping)
        {
            if (sf::Keyboard::isKeyPressed(pair.first))
            {
                return pair.second;
            }
        }
        return { Still, 0 };
    }
}
//----------------------------------------------------------------------------
int Player::whereToMove()
{
    return int(dirFromKey().x + dirFromKey().y);
}
//----------------------------------------------------------------------------
// remember to init future vars.
Player::Player(const Player &other) {
    m_rec = other.m_rec;
    m_speed = other.m_speed;
    m_state = other.m_state;
    m_textures = other.m_textures;
    m_type = other.m_type;
}
//----------------------------------------------------------------------------
int Player::getLife() const
{
    return m_life;
}
//----------------------------------------------------------------------------
int Player::getScore() const
{
    return m_score;
}
//----------------------------------------------------------------------------
void Player::setLevel(int level)
{
    m_level = level;
}
//----------------------------------------------------------------------------
bool Player::isDead()
{
    bool temp = m_died;
    m_died = false;
    return temp;
}
//----------------------------------------------------------------------------
void Player::setLife(int playerLife)
{
    m_life =  playerLife;
}
//----------------------------------------------------------------------------
void Player::reduceLife()
{
    m_life--;
}
//----------------------------------------------------------------------------
bool Player::didTakeGift()
{
    bool temp = m_didTakeGift;
    m_didTakeGift = false;
    return temp;
}
//----------------------------------------------------------------------------
int Player::getCoinsCollected() const {
    return m_coinsCollected;
}
//----------------------------------------------------------------------------
void Player::addScore(int playerScore)
{
    m_score += playerScore;
}
//----------------------------------------------------------------------------
void Player::addLife()
{
    m_life ++;
}
//----------------------------------------------------------------------------
void Player::handleCollision(GameObject& gameObject)
{
    if (&gameObject == this) return;
    // double dispatch
    gameObject.handleCollision(*this);
}
//----------------------------------------------------------------------------
void Player::handleCollision(Enemy& gameObject)
{
    m_life--;
    m_died = true;
}
//----------------------------------------------------------------------------
void Player::handleCollision(Coin& gameObject)
{
    m_score += (2 * m_level);
    m_coinsCollected++;
}
//----------------------------------------------------------------------------
void Player::handleCollision(Gift& gameObject)
{
    m_didTakeGift = true;
}
//----------------------------------------------------------------------------
void Player::handleCollision(Ladder& gameObject)
{
    m_rec.setTexture(m_textures[2]);
}
//----------------------------------------------------------------------------
void Player::handleCollision(Rope& gameObject)
{
    //ignore
}
//----------------------------------------------------------------------------