#pragma once
#include <iostream>
#include <vector>
#include <SFML\Graphics.hpp>
#include <string>
#include "Grid.h"

enum Powerup {
	MORESHOTS,
	GOTTAGOFAST,
	NODAMAGE,
	REPLENISH
};

class Powerups
{
public:
	Powerups(int state);
	~Powerups();
	void update();
	void render(sf::RenderWindow &window);
	sf::Vector2f getPosition();
	Powerup getState();
	void setState(int S);
	int pGridX;
	int pGridY;
	bool collected;
	bool shrink = false;
	Powerup currentPowerup = MORESHOTS;
private:
	
	sf::Vector2f m_position;
	float rotation;
	float maxRotation;
	float m_scale;
	sf::Texture PowerupTxt;
	sf::Texture PowerupTxt2;
	sf::Texture PowerupTxt3;
	sf::Texture PowerupTxt4;
	sf::Sprite PowerupSprite;
	sf::RectangleShape p_shape;
	Grid *m_Grid;
	
};