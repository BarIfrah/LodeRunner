#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <string>
#include "GameObject.h"
using namespace std;
using namespace sf;

class Board
{

public:
	Board();
	explicit Board(const string &file_name);
	char getType(int level, int row, int col);
	float getTime(int level) const;
	int getRows( int level) const;
	int getCols( int level) const;
	int getLevels() const;
	void getBlank(int level, int& x, int& y) const;

private:
	fstream m_file;
	vector<vector< vector<char>>> m_map;
	int m_levels;
	vector<int> m_rows;
	vector<int> m_cols;
	vector<float> m_time;

};