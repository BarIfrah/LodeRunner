#include "StatsBoard.h"
#include "macros.h"
//----------------------------------------------------------------------------
StatsBoard::StatsBoard()
{
    m_playerLife = 3;
	auto* gameFont = new Font();
	gameFont->loadFromFile("C:/Windows/Fonts/Arial.ttf");
	m_text.emplace_back(life, *gameFont);
	m_text.emplace_back(score, *gameFont);
	m_text.emplace_back(level, *gameFont);
	m_text.emplace_back(timer, *gameFont);

	m_text[0].setPosition(50, 15);
	m_text[1].setPosition(350, 15);
	m_text[2].setPosition(650, 15);
	m_text[3].setPosition(950, 15);
}
//----------------------------------------------------------------------------
void StatsBoard::Update(Player* playerObject, int game_level, const string &time)
{
	m_playerLife = playerObject->getLife();
	m_text[0].setString(life + to_string(m_playerLife));
	m_text[1].setString(score + to_string(playerObject->getScore()));
	m_text[2].setString(level + to_string(game_level));
	m_text[3].setString(timer + time);
}
//----------------------------------------------------------------------------
void StatsBoard::Draw(sf::RenderWindow& window) const
{
	for (int i = 0; i < m_text.size(); i++)
		window.draw(m_text[i]);
}
//----------------------------------------------------------------------------
bool StatsBoard::isOver() const
{
	return (m_playerLife) == 0; // returns true or false (if the player is dead dead)
}
//----------------------------------------------------------------------------