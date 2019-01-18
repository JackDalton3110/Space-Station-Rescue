#include "Tile.h"
#include <iostream>
Tile::Tile(float x, float y, int tileSize, float tileScale, int xPos, int yPos, sf::Font &font) :
	m_position(x, y),
	m_tileSize(tileSize),
	m_tileScale(tileScale),
	m_xPos(xPos),
	m_yPos(yPos),
	m_font(font)
{

	m_costText.setFont(m_font);
	m_costText.setString(std::to_string(m_cost));
	m_costText.setFillColor(sf::Color::Black);
	m_costText.setPosition(m_position);
	rectangle.setSize(sf::Vector2f(m_tileSize * m_tileScale, m_tileSize * m_tileScale));

	rectangle.setOutlineThickness(2);
	rectangle.setOutlineColor(sf::Color(200, 200, 200));
	rectangle.setPosition(x, y);

	vector.setSize(sf::Vector2f(25, 1));
	vector.setFillColor(sf::Color::Red);
	vector.setOutlineColor(sf::Color::Red);
	vector.setOutlineThickness(1);
	vector.setPosition(m_position.x + ((m_tileSize * m_tileScale) / 2), m_position.y + ((m_tileSize * m_tileScale) / 2));
	vector.setRotation(m_rotation);

	

}

Tile::~Tile()
{

}
/// <summary>
/// handles rotation of teh flow field vectors
/// Also sets the velocity of this tile depending on the rotation
/// </summary>
/// <param name="rot"></param>
void Tile::setRotation(float rot)
{
	m_rotation = rot;
	vector.setRotation(m_rotation);

	if (rot == 0)
	{
		setVelocity(1, 0);
	}
	else if (rot == 45)
	{
		setVelocity(1, 1);
	}
	else if (rot == 90)
	{
		setVelocity(0, 1);
	}
	else if (rot == 135)
	{
		setVelocity(-1, 1);
	}
	else if (rot == 180)
	{
		setVelocity(-1, 0);
	}
	else if (rot == 225)
	{
		setVelocity(-1, -1);
	}
	else if (rot == 270)
	{
		setVelocity(0, -1);
	}
	else if (rot == 315)
	{
		setVelocity(1, -1);
	}
	
}

/// <summary>
/// Sets the velocity of the tile
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
void Tile::setVelocity(int x, int y)
{
	m_velocity.x = x;
	m_velocity.y = y;

}

/// <summary>
/// Returns the velocity of the player
/// </summary>
/// <returns></returns>
sf::Vector2f Tile::getVelocity()
{
	return m_velocity;

}

/// <summary>
/// Sets the current state of the tile
/// depending on the tile type the tile is coloured differently 
/// 
/// </summary>
/// <param name="s"></param>
void Tile::setCurrentState(State s)
{
	m_currentState = s;

	switch (m_currentState)
	{
	case NONE:
		if (255 - (m_cost * 1.7) > 0)
		{
			rectangle.setFillColor(sf::Color(255 - (m_cost * 1.8), 255 - (m_cost * 1.8), 255));
		}
		else
		{
			rectangle.setFillColor(sf::Color(255, 255, 255));
		}

		break;
	case START:
		rectangle.setFillColor(sf::Color::Green);
		break;
	case GOAL:
		rectangle.setFillColor(sf::Color::Red);
		break;
	case OBSTACLE:
		rectangle.setFillColor(sf::Color(45, 45, 45));
		rectangle.setOutlineThickness(0);
		break;
	case PATH:
		rectangle.setFillColor(sf::Color(50, 255, 255));
		break;
	case SPAWN:
		rectangle.setFillColor(sf::Color::Red);
		break;
	case NEST:
		rectangle.setFillColor(sf::Color::Blue);
		break;
	case SWEEPER:
		rectangle.setFillColor(sf::Color::Magenta);
		break;
	default:
		break;
	}
}

/// <summary>
/// Get current state of the tile
/// </summary>
/// <returns></returns>
State Tile::getCurrentState()
{
	return m_currentState;
}

/// <summary>
/// Sets the draw state of the tyle
/// </summary>
/// <param name="ds"></param>
void Tile::setDrawState(Draw ds) {

	m_drawState = ds;
}

/// <summary>
/// Returns the drawstate of the tile
/// </summary>
/// <returns></returns>
Draw Tile::getDrawState() {
	return m_drawState;
}

/// <summary>
/// Sets the cost of teh tile
/// </summary>
/// <param name="cost"></param>
void Tile::setCost(int cost)
{
	m_cost = cost;
	m_costText.setString(std::to_string(m_cost));

}
/// <summary>
/// returns the cost of the tile
/// </summary>
/// <returns></returns>
int Tile::getCost()
{
	return m_cost;
}

/// <summary>
/// Sets the previous tile that was visited
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
void Tile::setPrevious(int x, int y) {

	m_previous = std::make_pair(x, y);
}

/// <summary>
/// Draws the vectors of the flowfield on the tile
/// If commented outthe red vectors will disappear 
/// </summary>
/// <param name="window"></param>
void Tile::render(sf::RenderWindow &window)
{
	if (m_cost == 0) {
		vector.setSize(sf::Vector2f(1, 1));
	}
	else {
		vector.setSize(sf::Vector2f(25, 1));
	}

	window.draw(rectangle);

	if (m_currentState == NONE || m_currentState == PATH)
	{
		window.draw(vector);
	}
	

}