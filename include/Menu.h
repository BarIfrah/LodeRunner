#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <string>
using namespace sf;
using namespace std;

class Menu
{
public:
	explicit Menu(RectangleShape background = RectangleShape());
	void showMenu(RenderWindow& window);


private:
	RectangleShape m_background, m_exit, m_start, m_menu, m_howToPlayButton, m_howToPlay, m_back;
	vector<Texture*> m_startTextures, m_exitTextures, m_howtoTextures;
	void handleClick(const sf::Vector2f& location, RenderWindow& window);
	void handleHover(const sf::Vector2f& location);
	bool m_toStart = false;
	bool m_showHowto = false;
};