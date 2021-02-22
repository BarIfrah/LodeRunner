#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <string>
#include "Board.h"
#include "StatsBoard.h"
#include "GameObject.h"
#include <SFML/Audio.hpp>
#include "Player.h"
#include <memory>
using namespace std;
using namespace sf;

class MovingObject;
class StaticObject;

class Controller
{

public:
    explicit Controller(string file_name = " ");
    void run();
    GameObject* getStaticObject(int index) const;
    int getStaticSize() const;
    bool checkTrap(MovingObject& gameObject);

private:
    void draw();
    void handleEvents();
    static Music* getMusic();
    void updateGameObjects(Time time);
    void handleCollisions(MovingObject& gameObject);
    void resetLevel();
    void createObjectDataStructure();
    vector <Texture*> buildTextures(vector<string> names);
    Texture* buildTexture(const string &name);
    void GameOver();
    void tookGift();
    void createEnemy(); // creates enemy when bad gift is collected
    void dig(bool direction);
    void freeTrapped(GameObject& wallToCheck);
    void createTextureVectors();
    Vector2f backToBasic(Vector2f location);

    vector<unique_ptr<GameObject>> m_staticObjects;
    vector<unique_ptr<MovingObject>> m_movingObjects;
    vector<unique_ptr<GameObject>> m_deletedWalls; // holds dug walls

    RenderWindow m_window;	//the building window
    Board m_board;
    StatsBoard m_stats;
    Clock m_clock;
    vector<Texture*> m_Playertexture; //player textures vector
    vector<Texture*> m_Renemytexture; //random enemy textures vector
    vector<Texture*> m_Senemytexture; //smart enemy textures vector
    vector<Texture*> m_Penemytexture; //patrol enemy textures vector
    int m_level = 1, m_playerIndex, m_levelCoins = 0, m_totalLevels, m_score = 0;
    float m_levelTime;
    bool m_unlimitedTime = false;
    Music *m_music;
    RectangleShape m_background;
    Player* m_player;
};