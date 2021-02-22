#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include <vector>
using namespace sf;
using namespace std;

class MovingObject :public GameObject
{
public:
	MovingObject(char type = '#', sf::Vector2f size = sf::Vector2f(0, 0), sf::Vector2f location = sf::Vector2f(0, 0), Texture* texture = new Texture(), const vector <Texture*> & textures = {} ,int speed = 1);
	void move(Controller* controller, Time time);
	virtual int whereToMove() = 0;
	void setTrapped() { m_rec.move(0, m_rec.getSize().y); m_isTrapped = true; };  //sets an enemy to be stuck in a hole
	void setFree() { m_rec.move(0, -(m_rec.getSize().y+1)); m_isTrapped = false; }; //sets it free

protected:
	bool canMove(int direction, Controller* controller, float criticalMovement) const;
	void fall(Controller* controller);
	void nextTexture();
	vector <Texture*> m_textures;
	int  m_state = 0;
	float m_speed;
	bool m_isTrapped = false; // if trapped in  a hole
};