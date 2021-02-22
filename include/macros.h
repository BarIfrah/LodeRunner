#pragma once
#include <SFML/Graphics.hpp>

constexpr auto STARTING_X = 90;
constexpr auto STARTING_Y = 85;

const auto endScreenTime = 5;
constexpr auto Window_width = 1500;
constexpr auto Window_height = 1000;

constexpr auto Board_Height = 900;
constexpr auto Board_Width = 1400;

constexpr auto Left = 0;
constexpr auto Right = 1;
constexpr auto Up = 2;
constexpr auto Down = 3;
constexpr auto Still = 4;

constexpr auto PlayerSpeed = 150;
constexpr auto EnemySpeed = 90;
constexpr auto patrolRadius = 250;

constexpr auto life = "Life: ";
constexpr auto score = "Score: ";
constexpr auto timer = "Time: ";
constexpr auto level = "Level: ";


constexpr auto player = '@';
constexpr auto ladder = 'H';
constexpr auto rope = '-';
constexpr auto enemy = '%';
constexpr auto wall = '#';
constexpr auto coin = '*';
constexpr auto gift = '&';
constexpr auto blank = ' ';