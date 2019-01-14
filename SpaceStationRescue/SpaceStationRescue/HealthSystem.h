#pragma once
#pragma once
#include <SFML\Graphics.hpp>
#include <string>
#include <iostream>
#include <sstream>

class HealthSystem
{
public:
	HealthSystem();
	~HealthSystem();

	bool dead = false;
	void update();
	void render(sf::RenderWindow &window);
	void setPosition(float x, float y);
	sf::Vector2f m_position;
	int m_healthValue;
	sf::Sprite healthSprite;

private:
	sf::Texture health3_0Txt;
	sf::Texture health2_5Txt;
	sf::Texture health2_0Txt;
	sf::Texture health1_5Txt;
	sf::Texture health1_0Txt;
	sf::Texture health0_5Txt;
	sf::Texture health0_0Txt;

	sf::RectangleShape outerRect;
	sf::RectangleShape innerRect;
};