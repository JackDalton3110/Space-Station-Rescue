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
	Powerups(int state, sf::Vector2f pos);
	~Powerups();
	void update();
	void render(sf::RenderWindow &window);
	sf::Vector2f getPosition();
	Powerup getState();
	void setState(int S);

	bool collected;
	Powerup currentPowerup;
private:
	void setImage(Powerup S);
	
	sf::Vector2f m_position;
	float rotation;
	float maxRotation;
	float m_scale;
	sf::Texture PowerupTxt;
	sf::Sprite PowerupSprite;
	sf::RectangleShape p_shape;
	Grid *m_Grid;
	int pGridX;
	int pGridY;
};