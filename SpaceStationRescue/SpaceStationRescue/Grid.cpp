#include "Game.h"
#include <limits>
#include <list>
#include <queue>
#include "Grid.h"

/// <summary>
/// 
/// </summary>
Grid::Grid()
{
	for (int i = 0; i < m_gridSize; i++)
	{
		for (int j = 0; j < m_gridSize; j++)
		{
			m_tileGrid[j][i] = new Tile(x + 10, y + 10, m_tileSize, m_tileScale, j, i, m_font);
			x = x + m_tileSize * m_tileScale;
		}

		x = 0;
		y = y + m_tileSize * m_tileScale;
	}

	for (int i = 0; i < m_gridSize; i++)
	{

		m_tileGrid[0][i]->setCurrentState(OBSTACLE);
		m_tileGrid[i][0]->setCurrentState(OBSTACLE);
		m_tileGrid[m_gridSize - 1][i]->setCurrentState(OBSTACLE);
		m_tileGrid[i][m_gridSize - 1]->setCurrentState(OBSTACLE);
	}
}

/// <summary>
/// 
/// </summary>



void Grid::reset()
{

	m_startTile = NULL;
	m_goalTile = NULL;

	for (int i = 0; i < m_gridSize; i++)
	{
		for (int j = 0; j < m_gridSize; j++)
		{
			m_tileGrid[j][i]->setCost(0);
			m_tileGrid[j][i]->setCurrentState(NONE);

		}

	}

	for (int i = 0; i < m_gridSize; i++)
	{

		m_tileGrid[0][i]->setCurrentState(OBSTACLE);
		m_tileGrid[i][0]->setCurrentState(OBSTACLE);
		m_tileGrid[m_gridSize - 1][i]->setCurrentState(OBSTACLE);
		m_tileGrid[i][m_gridSize - 1]->setCurrentState(OBSTACLE);
	}
}

/// <summary>
/// 
/// </summary>
void Grid::update()
{
	for (int i = 0; i < m_gridSize; i++)
	{
		for (int j = 0; j < m_gridSize; j++)
		{
			m_tileGrid[i][j]->update();
		}

	}
}

void Grid::initGrid(int posX, int posY)
{
	for (int i = 0; i < m_gridSize; i++)
	{
		for (int j = 0; j < m_gridSize; j++)
		{
			if (m_tileGrid[i][j]->getCurrentState() == OBSTACLE)
			{
				m_tileGrid[i][j]->setCost(std::numeric_limits<int>::max());
			}
		}

	}

	for (int i = 0; i < m_gridSize; i++)
	{
		for (int j = 0; j < m_gridSize; j++)
		{
			if (m_tileGrid[i][j]->getCurrentState() == NONE)
			{
				m_tileGrid[i][j]->setCost(0);
			}
		}

	}

	std::list<Tile> tileQueue;


	tileQueue.push_back(*m_tileGrid[posX][posY]);

	m_tileGrid[posX][posY]->setCost(0);
	int i = 0;

	auto iter = tileQueue.begin();

	//for (; iter != endIter; iter++) {
	while (tileQueue.size() != 0) {
		i++;
		std::cout << i << std::endl;

		if (iter->m_xPos != m_gridSize - 1 && m_tileGrid[iter->m_xPos + 1][iter->m_yPos]->getCost() == 0 && m_tileGrid[iter->m_xPos + 1][iter->m_yPos]->getCurrentState() != GOAL)
		{
			m_tileGrid[iter->m_xPos + 1][iter->m_yPos]->setCost(m_tileGrid[iter->m_xPos][iter->m_yPos]->getCost() + 1);
			m_tileGrid[iter->m_xPos + 1][iter->m_yPos]->setRotation(180);
			m_tileGrid[iter->m_xPos + 1][iter->m_yPos]->setPrevious(m_tileGrid[iter->m_xPos][iter->m_yPos]->m_xPos, m_tileGrid[iter->m_xPos][iter->m_yPos]->m_yPos);
			tileQueue.push_back(*m_tileGrid[iter->m_xPos + 1][iter->m_yPos]);
		}

		if (iter->m_xPos != m_gridSize - 1 && m_tileGrid[iter->m_xPos][iter->m_yPos + 1]->getCost() == 0 && m_tileGrid[iter->m_xPos][iter->m_yPos + 1]->getCurrentState() != GOAL)
		{
			m_tileGrid[iter->m_xPos][iter->m_yPos + 1]->setCost(m_tileGrid[iter->m_xPos][iter->m_yPos]->getCost() + 1);
			m_tileGrid[iter->m_xPos][iter->m_yPos + 1]->setRotation(270);
			m_tileGrid[iter->m_xPos][iter->m_yPos + 1]->setPrevious(m_tileGrid[iter->m_xPos][iter->m_yPos]->m_xPos, m_tileGrid[iter->m_xPos][iter->m_yPos]->m_yPos);
			tileQueue.push_back(*m_tileGrid[iter->m_xPos][iter->m_yPos + 1]);
		}

		if (iter->m_xPos != 0 && m_tileGrid[iter->m_xPos - 1][iter->m_yPos]->getCost() == 0 && m_tileGrid[iter->m_xPos - 1][iter->m_yPos]->getCurrentState() != GOAL)
		{
			m_tileGrid[iter->m_xPos - 1][iter->m_yPos]->setCost(m_tileGrid[iter->m_xPos][iter->m_yPos]->getCost() + 1);
			m_tileGrid[iter->m_xPos - 1][iter->m_yPos]->setRotation(0);
			m_tileGrid[iter->m_xPos - 1][iter->m_yPos]->setPrevious(m_tileGrid[iter->m_xPos][iter->m_yPos]->m_xPos, m_tileGrid[iter->m_xPos][iter->m_yPos]->m_yPos);
			tileQueue.push_back(*m_tileGrid[iter->m_xPos - 1][iter->m_yPos]);
		}

		if (iter->m_yPos != 0 && m_tileGrid[iter->m_xPos][iter->m_yPos - 1]->getCost() == 0 && m_tileGrid[iter->m_xPos][iter->m_yPos - 1]->getCurrentState() != GOAL)
		{
			m_tileGrid[iter->m_xPos][iter->m_yPos - 1]->setCost(m_tileGrid[iter->m_xPos][iter->m_yPos]->getCost() + 1);
			m_tileGrid[iter->m_xPos][iter->m_yPos - 1]->setRotation(90);
			m_tileGrid[iter->m_xPos][iter->m_yPos - 1]->setPrevious(m_tileGrid[iter->m_xPos][iter->m_yPos]->m_xPos, m_tileGrid[iter->m_xPos][iter->m_yPos]->m_yPos);
			tileQueue.push_back(*m_tileGrid[iter->m_xPos][iter->m_yPos - 1]);
		}
		if (iter->m_xPos != m_gridSize - 1 && iter->m_yPos != m_gridSize - 1 && m_tileGrid[iter->m_xPos + 1][iter->m_yPos + 1]->getCost() == 0 && m_tileGrid[iter->m_xPos + 1][iter->m_yPos + 1]->getCurrentState() != GOAL)
		{
			m_tileGrid[iter->m_xPos + 1][iter->m_yPos + 1]->setCost(m_tileGrid[iter->m_xPos][iter->m_yPos]->getCost() + 1);
			m_tileGrid[iter->m_xPos + 1][iter->m_yPos + 1]->setRotation(202.5);
			m_tileGrid[iter->m_xPos + 1][iter->m_yPos + 1]->setPrevious(m_tileGrid[iter->m_xPos][iter->m_yPos]->m_xPos, m_tileGrid[iter->m_xPos][iter->m_yPos]->m_yPos);
			tileQueue.push_back(*m_tileGrid[iter->m_xPos + 1][iter->m_yPos + 1]);
		}
		if (iter->m_yPos != m_gridSize - 1 && iter->m_xPos != 0 && m_tileGrid[iter->m_xPos - 1][iter->m_yPos + 1]->getCost() == 0 && m_tileGrid[iter->m_xPos - 1][iter->m_yPos + 1]->getCurrentState() != GOAL)
		{
			m_tileGrid[iter->m_xPos - 1][iter->m_yPos + 1]->setCost(m_tileGrid[iter->m_xPos][iter->m_yPos]->getCost() + 1);
			m_tileGrid[iter->m_xPos - 1][iter->m_yPos + 1]->setRotation(292.5);
			m_tileGrid[iter->m_xPos - 1][iter->m_yPos + 1]->setPrevious(m_tileGrid[iter->m_xPos][iter->m_yPos]->m_xPos, m_tileGrid[iter->m_xPos][iter->m_yPos]->m_yPos);
			tileQueue.push_back(*m_tileGrid[iter->m_xPos - 1][iter->m_yPos + 1]);
		}
		if (iter->m_yPos != 0 && iter->m_xPos != 0 && m_tileGrid[iter->m_xPos - 1][iter->m_yPos - 1]->getCost() == 0 && m_tileGrid[iter->m_xPos - 1][iter->m_yPos - 1]->getCurrentState() != GOAL)
		{
			m_tileGrid[iter->m_xPos - 1][iter->m_yPos - 1]->setCost(m_tileGrid[iter->m_xPos][iter->m_yPos]->getCost() + 1);
			m_tileGrid[iter->m_xPos - 1][iter->m_yPos - 1]->setRotation(45);
			m_tileGrid[iter->m_xPos - 1][iter->m_yPos - 1]->setPrevious(m_tileGrid[iter->m_xPos][iter->m_yPos]->m_xPos, m_tileGrid[iter->m_xPos][iter->m_yPos]->m_yPos);
			tileQueue.push_back(*m_tileGrid[iter->m_xPos - 1][iter->m_yPos - 1]);
		}
		if (iter->m_xPos != m_gridSize - 1 && iter->m_yPos != 0 && m_tileGrid[iter->m_xPos + 1][iter->m_yPos - 1]->getCost() == 0 && m_tileGrid[iter->m_xPos + 1][iter->m_yPos - 1]->getCurrentState() != GOAL)
		{
			m_tileGrid[iter->m_xPos + 1][iter->m_yPos - 1]->setCost(m_tileGrid[iter->m_xPos][iter->m_yPos]->getCost() + 1);
			m_tileGrid[iter->m_xPos + 1][iter->m_yPos - 1]->setRotation(112.5);
			m_tileGrid[iter->m_xPos + 1][iter->m_yPos - 1]->setPrevious(m_tileGrid[iter->m_xPos][iter->m_yPos]->m_xPos, m_tileGrid[iter->m_xPos][iter->m_yPos]->m_yPos);
			tileQueue.push_back(*m_tileGrid[iter->m_xPos + 1][iter->m_yPos - 1]);
		}

		//tileQueue.remove(*iter);
		iter++;
		tileQueue.pop_front();
	}

	if (m_startTile != NULL)
	{
		getPath(*m_startTile);
	}


}
void Grid::getPath(Tile m_startTile)
{


	std::list<Tile> tileQueue;


	tileQueue.push_back(m_startTile);

	auto iter = tileQueue.begin();
	while (iter->m_cost != 0 && m_tileGrid[iter->m_previous.first][iter->m_previous.second]->getCurrentState() != GOAL) 
	{
		m_tileGrid[iter->m_previous.first][iter->m_previous.second]->setCurrentState(PATH);
		tileQueue.push_back(*m_tileGrid[iter->m_previous.first][iter->m_previous.second]);
		iter++;
	}



}


/// <summary>
/// 
/// </summary>
void Grid::render(sf::RenderWindow &window)
{
	window.clear(sf::Color::White);
	for (int i = 0; i < m_gridSize; i++)
	{
		for (int j = 0; j < m_gridSize; j++)
		{
			m_tileGrid[i][j]->render(window);
		}

	}

}