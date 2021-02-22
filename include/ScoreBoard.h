#include "macros.h"
#include <vector>
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

class ScoreBoard
{
public:
	ScoreBoard();
	void Update(int life, int score);
	void Draw(sf::RenderWindow& window);

private:
	vector<Text> m_text;
};
