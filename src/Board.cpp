#include <vector>
#include "Board.h"
#include <iostream>
using namespace std;
using namespace sf;
//----------------------------------------------------------------------------
//constructor
Board::Board() : m_file(fstream()), m_cols(), m_rows(), m_levels(0), m_map(vector<vector<vector<char>>>())
{
}
//----------------------------------------------------------------------------
//constructor
// here we build a 3d vector that holds in every cell a 2d map of the game.
// we use this to move forward in the levels.
Board::Board(const string &file_name)
{
    m_file.open(file_name);
    char charFromFile = m_file.peek();	//check if the file is empty or not
    if (charFromFile == '\0')	//if empty
    {
        m_rows = m_cols = {};
    }
    else
    {   
        m_file >> m_levels ;
        for (int i = 0; i < m_levels; ++i) {
            vector<vector<char>> currentMap = {};
            m_file.get(charFromFile);	//get the \n
            int temp;
            m_file >> temp;
            m_rows.emplace_back(temp);
            m_file >> temp;
            m_cols.emplace_back(temp);
            m_file >> temp;
            m_time.emplace_back(temp);
            m_file.get(charFromFile);	//get the \n

            //auto size = sf::Vector2f(Board_Width / float(m_cols[i]), Board_Height / float(m_rows[i]));
            for (int j = 0; j < m_rows[i]; j++) {
                vector<char> currentLine;
                for (int k = 0; k < m_cols[i]; k++) {
                    m_file.get(charFromFile);
                    currentLine.push_back(charFromFile);
                }
                m_file.get(charFromFile);
                currentMap.push_back(currentLine);
            }
            m_map.emplace_back(currentMap);
        }
    }
}
//----------------------------------------------------------------------------
float Board::getTime(int currentLevel) const
{
    return m_time[currentLevel];
}
//----------------------------------------------------------------------------
char Board::getType(int currentLevel, int row, int col)
{
    return m_map[currentLevel][row][col];
}
//----------------------------------------------------------------------------
int Board::getRows(int currentLevel) const
{
    return m_rows[currentLevel];
}
//----------------------------------------------------------------------------
int Board::getCols( int currentLevel) const
{
    return m_cols[currentLevel];
}
//----------------------------------------------------------------------------
int Board::getLevels() const
{
    return m_levels;
}
//----------------------------------------------------------------------------
void Board::getBlank(int currentLevel, int& x, int& y) const
{
    for (int i = 0; i < m_rows[currentLevel-1]; i++)
        for (int j = 0; j < m_cols[currentLevel-1]; j++)
            if (m_map[currentLevel - 1][i][j] == blank)
            {
                x = i;
                y = j;
                return;
            }
}
//----------------------------------------------------------------------------