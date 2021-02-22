#include "PatrolEnemy.h"

PatrolEnemy::PatrolEnemy(char type, sf::Vector2f size, sf::Vector2f location, Texture* texture, const vector <Texture*>& textures, int speed, int radius)
	: Enemy(type, size, location, texture, textures, speed), m_patrolRadius(radius)
{}


int PatrolEnemy::whereToMove()
{
	m_counter++;
	if (m_counter == m_patrolRadius)
	{
		m_direction = !m_direction;
		m_counter = 0;
	}
	if (m_direction) return Left;
	else return Right;
}
