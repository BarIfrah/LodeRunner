#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "Player.h"
using namespace sf;
using namespace std;

class StatsBoard
{
public:
	StatsBoard();
	void Update(Player* player, int game_level, const string &time);
	void Draw(sf::RenderWindow& window) const;
	bool isOver() const;

private:
	vector<Text> m_text;
	int m_playerLife;
};
