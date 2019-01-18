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
	int mySampleMap[55][55] = { 
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1 },
	{ 1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1 },
	{ 1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1 },
	{ 1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1 },
	{ 1,1,1,0,0,0,0,0,2,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1 },
	{ 1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,1,1 },
	{ 1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1 },
	{ 1,1,1,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1 },
	{ 1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1 },
	{ 1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1 },
	{ 1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,0,3,0,0,0,0,0,0,0,0,0,1,1 },
	{ 1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1 },
	{ 1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1 },
	{ 1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1 },
	{ 1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1 },
	{ 1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1 },
	{ 1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1 },
	{ 1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1 },
	{ 1,1,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,1,1,1,1,1 },
	{ 1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1 },
	{ 1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1 },
	{ 1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1 },
	{ 1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,1,1,1,1,1 },
	{ 1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 }};


	for (int i = 0; i < m_gridSize; i++)
	{
		for (int j = 0; j < m_gridSize; j++)
		{
			m_tileGrid[j][i] = new Tile(x + 10, y + 10, m_tileSize, m_tileScale, j, i, m_font);
			x = x + m_tileSize * m_tileScale;
			
			if (mySampleMap[i][j] == 1)
			{
				m_tileGrid[j][i]->setCurrentState(OBSTACLE);
			}
			else if (mySampleMap[i][j] == 0)
			{
				m_tileGrid[j][i]->setCurrentState(NONE);
			}
			else if (mySampleMap[i][j] == 2)
			{
				m_tileGrid[j][i]->setCurrentState(SPAWN);
				m_spawnPoints.push_back(m_tileGrid[j][i]);
			}
			else if (mySampleMap[i][j] == 3)
			{
				m_tileGrid[j][i]->setCurrentState(NEST);
				m_nestPoints.push_back(m_tileGrid[j][i]);
			}
			else if (mySampleMap[i][j] == 4)
			{
				m_tileGrid[j][i]->setCurrentState(SWEEPER);
				m_sweeperSpawn = m_tileGrid[j][i];
			}
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

	//Set up second view for minimap, scale and positioned to the top right hand corner
	miniMapView.setViewport(sf::FloatRect(0.73f, 0.02f, 0.25f, 0.25f));
	miniMapView.setSize(1920, 1080);
	miniMapView.setCenter(960, 540);

	//gameView.setSize(1920, 1080);
	//gameView.setCenter(960, 540);

	//initGrid();

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
				m_tileGrid[i][j]->setCost(1);
				m_tileGrid[i][j]->checked = false;
				m_tileGrid[i][j]->setVelocity(-1,0);
				m_tileGrid[i][j]->setRotation(180);
			}

		}

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
/// Updates the flowfield thats used for the predator pathfinding
/// Pos x and Pos Y is the players grid position, the player is acting as the goal to the preadtors
/// radius is how many loops the updates cost loop does, the higher the ny,be the more of the map is updates
/// initially the entire maps costs are updated but as the game runs more than half of the map is updated as the player moves for efficiency 
/// 
/// when called all the tiles that arent obstacles are set to unchecked
/// 
/// the tiles are then checked around the player going further away, updating the tiles costs (how far away they are from the player
/// As it does this the rotation for the tile vector is set to point at the previous tile
/// 
/// These checks are done in 8 directions
/// </summary>
/// <param name="posX"></param>
/// <param name="posY"></param>
/// <param name="radius"></param>
void Grid::updateCost(int posX, int posY, int radius)
{

	for (int i = 0; i < m_gridSize; i++)
	{
		for (int j = 0; j < m_gridSize; j++)
		{
			if (m_tileGrid[i][j]->getCurrentState() != OBSTACLE)
			{
				
				m_tileGrid[i][j]->checked = false;
			}

		}

	}

	std::list<Tile> tileQueue;

	tileQueue.push_back(*m_tileGrid[posX][posY]);

	m_tileGrid[posX][posY]->setCost(0);

	int i = 0;
	int j = 0;

	auto iter = tileQueue.begin();

	while (tileQueue.size() !=0 && i < radius ) {
		i++;


		if (iter->m_xPos != 0 && m_tileGrid[iter->m_xPos - 1][iter->m_yPos]->getCurrentState() != OBSTACLE && m_tileGrid[iter->m_xPos - 1][iter->m_yPos]->checked == false)
		{
			m_tileGrid[iter->m_xPos - 1][iter->m_yPos]->checked = true;
			m_tileGrid[iter->m_xPos - 1][iter->m_yPos]->setCost(m_tileGrid[iter->m_xPos][iter->m_yPos]->getCost() + 1);
			m_tileGrid[iter->m_xPos - 1][iter->m_yPos]->setRotation(0);
			m_tileGrid[iter->m_xPos - 1][iter->m_yPos]->setPrevious(m_tileGrid[iter->m_xPos][iter->m_yPos]->m_xPos, m_tileGrid[iter->m_xPos][iter->m_yPos]->m_yPos);
			tileQueue.push_back(*m_tileGrid[iter->m_xPos - 1][iter->m_yPos]);
			j++;
		}
	

		if (iter->m_yPos != 0 && m_tileGrid[iter->m_xPos][iter->m_yPos - 1]->getCurrentState() !=OBSTACLE && m_tileGrid[iter->m_xPos][iter->m_yPos - 1]->checked == false)
		{
			m_tileGrid[iter->m_xPos][iter->m_yPos - 1]->checked = true;
			m_tileGrid[iter->m_xPos][iter->m_yPos - 1]->setCost(m_tileGrid[iter->m_xPos][iter->m_yPos]->getCost() + 1);
			m_tileGrid[iter->m_xPos][iter->m_yPos - 1]->setRotation(90);
			m_tileGrid[iter->m_xPos][iter->m_yPos - 1]->setPrevious(m_tileGrid[iter->m_xPos][iter->m_yPos]->m_xPos, m_tileGrid[iter->m_xPos][iter->m_yPos]->m_yPos);
			tileQueue.push_back(*m_tileGrid[iter->m_xPos][iter->m_yPos - 1]);
			j++;
		}

		if (iter->m_xPos != m_gridSize - 1 && m_tileGrid[iter->m_xPos + 1][iter->m_yPos]->getCurrentState() !=OBSTACLE && m_tileGrid[iter->m_xPos + 1][iter->m_yPos]->checked == false)
		{
			m_tileGrid[iter->m_xPos + 1][iter->m_yPos]->checked = true;
			m_tileGrid[iter->m_xPos + 1][iter->m_yPos]->setCost(m_tileGrid[iter->m_xPos][iter->m_yPos]->getCost() + 1);
			m_tileGrid[iter->m_xPos + 1][iter->m_yPos]->setRotation(180);
			m_tileGrid[iter->m_xPos + 1][iter->m_yPos]->setPrevious(m_tileGrid[iter->m_xPos][iter->m_yPos]->m_xPos, m_tileGrid[iter->m_xPos][iter->m_yPos]->m_yPos);
			tileQueue.push_back(*m_tileGrid[iter->m_xPos + 1][iter->m_yPos]);
			j++;
		}

		if (iter->m_xPos != m_gridSize - 1 && m_tileGrid[iter->m_xPos][iter->m_yPos + 1]->getCurrentState() != OBSTACLE && m_tileGrid[iter->m_xPos][iter->m_yPos + 1]->checked == false)
		{
			m_tileGrid[iter->m_xPos][iter->m_yPos + 1]->checked = true;
			m_tileGrid[iter->m_xPos][iter->m_yPos + 1]->setCost(m_tileGrid[iter->m_xPos][iter->m_yPos]->getCost() + 1);
			m_tileGrid[iter->m_xPos][iter->m_yPos + 1]->setRotation(270);
			m_tileGrid[iter->m_xPos][iter->m_yPos + 1]->setPrevious(m_tileGrid[iter->m_xPos][iter->m_yPos]->m_xPos, m_tileGrid[iter->m_xPos][iter->m_yPos]->m_yPos);
			tileQueue.push_back(*m_tileGrid[iter->m_xPos][iter->m_yPos + 1]);
			j++;
		}
		if (iter->m_yPos != 0 && iter->m_xPos != 0 && m_tileGrid[iter->m_xPos - 1][iter->m_yPos - 1]->getCurrentState() !=OBSTACLE && m_tileGrid[iter->m_xPos - 1][iter->m_yPos - 1]->checked == false)
		{
			m_tileGrid[iter->m_xPos - 1][iter->m_yPos - 1]->checked = true;
			m_tileGrid[iter->m_xPos - 1][iter->m_yPos - 1]->setCost(m_tileGrid[iter->m_xPos][iter->m_yPos]->getCost() + 1);
		

			if (m_tileGrid[iter->m_xPos - 1][iter->m_yPos]->getCurrentState() == OBSTACLE)
			{
				m_tileGrid[iter->m_xPos - 1][iter->m_yPos - 1]->setRotation(0);

			}
			else if (m_tileGrid[iter->m_xPos][iter->m_yPos - 1]->getCurrentState() == OBSTACLE)
			{
				m_tileGrid[iter->m_xPos - 1][iter->m_yPos - 1]->setRotation(90);

			}
			else
			{
				m_tileGrid[iter->m_xPos - 1][iter->m_yPos - 1]->setRotation(45);

			}
	
			m_tileGrid[iter->m_xPos - 1][iter->m_yPos - 1]->setPrevious(m_tileGrid[iter->m_xPos][iter->m_yPos]->m_xPos, m_tileGrid[iter->m_xPos][iter->m_yPos]->m_yPos);
			tileQueue.push_back(*m_tileGrid[iter->m_xPos - 1][iter->m_yPos - 1]);
			j++;
		}
		if (iter->m_xPos != m_gridSize - 1 && iter->m_yPos != 0 && m_tileGrid[iter->m_xPos + 1][iter->m_yPos - 1]->getCurrentState() != OBSTACLE && m_tileGrid[iter->m_xPos + 1][iter->m_yPos - 1]->checked == false)
		{
			m_tileGrid[iter->m_xPos + 1][iter->m_yPos - 1]->checked = true;
			m_tileGrid[iter->m_xPos + 1][iter->m_yPos - 1]->setCost(m_tileGrid[iter->m_xPos][iter->m_yPos]->getCost() + 1);
			if (m_tileGrid[iter->m_xPos][iter->m_yPos - 1]->getCurrentState() == OBSTACLE)
			{
				m_tileGrid[iter->m_xPos + 1][iter->m_yPos - 1]->setRotation(90);
				
			}
			else if(m_tileGrid[iter->m_xPos + 1][iter->m_yPos]->getCurrentState() == OBSTACLE)
			{
				m_tileGrid[iter->m_xPos + 1][iter->m_yPos - 1]->setRotation(180);
			
			}
			else
			{
				m_tileGrid[iter->m_xPos + 1][iter->m_yPos - 1]->setRotation(135);
			
			}
			m_tileGrid[iter->m_xPos + 1][iter->m_yPos - 1]->setPrevious(m_tileGrid[iter->m_xPos][iter->m_yPos]->m_xPos, m_tileGrid[iter->m_xPos][iter->m_yPos]->m_yPos);
			tileQueue.push_back(*m_tileGrid[iter->m_xPos + 1][iter->m_yPos - 1]);
			j++;
		}
		if (iter->m_xPos != m_gridSize - 1 && m_tileGrid[iter->m_xPos + 1][iter->m_yPos + 1]->getCurrentState() != OBSTACLE && m_tileGrid[iter->m_xPos + 1][iter->m_yPos + 1]->checked == false)
		{
			m_tileGrid[iter->m_xPos + 1][iter->m_yPos + 1]->checked = true;
			m_tileGrid[iter->m_xPos + 1][iter->m_yPos + 1]->setCost(m_tileGrid[iter->m_xPos][iter->m_yPos]->getCost() + 1);

			if (m_tileGrid[iter->m_xPos][iter->m_yPos + 1]->getCurrentState() == OBSTACLE)
			{
				m_tileGrid[iter->m_xPos + 1][iter->m_yPos + 1]->setRotation(270);

			}
			else if (m_tileGrid[iter->m_xPos + 1][iter->m_yPos]->getCurrentState() == OBSTACLE)
			{
				m_tileGrid[iter->m_xPos + 1][iter->m_yPos + 1]->setRotation(180);

			}
			else
			{
				m_tileGrid[iter->m_xPos + 1][iter->m_yPos + 1]->setRotation(225);

			}
			m_tileGrid[iter->m_xPos + 1][iter->m_yPos + 1]->setPrevious(m_tileGrid[iter->m_xPos][iter->m_yPos]->m_xPos, m_tileGrid[iter->m_xPos][iter->m_yPos]->m_yPos);
			tileQueue.push_back(*m_tileGrid[iter->m_xPos + 1][iter->m_yPos + 1]);
			j++;
		}
		if (iter->m_yPos != m_gridSize - 1 && m_tileGrid[iter->m_xPos - 1][iter->m_yPos + 1]->getCurrentState() != OBSTACLE && m_tileGrid[iter->m_xPos - 1][iter->m_yPos + 1]->checked == false)
		{
			m_tileGrid[iter->m_xPos - 1][iter->m_yPos + 1]->checked = true;
			m_tileGrid[iter->m_xPos - 1][iter->m_yPos + 1]->setCost(m_tileGrid[iter->m_xPos][iter->m_yPos]->getCost() + 1);
			m_tileGrid[iter->m_xPos - 1][iter->m_yPos + 1]->setRotation(315);

			if (m_tileGrid[iter->m_xPos][iter->m_yPos + 1]->getCurrentState() == OBSTACLE)
			{
				m_tileGrid[iter->m_xPos - 1][iter->m_yPos + 1]->setRotation(270);

			}
			else if (m_tileGrid[iter->m_xPos - 1][iter->m_yPos]->getCurrentState() == OBSTACLE)
			{
				m_tileGrid[iter->m_xPos - 1][iter->m_yPos + 1]->setRotation(0);

			}
			else
			{
				m_tileGrid[iter->m_xPos - 1][iter->m_yPos + 1]->setRotation(315);

			}
			m_tileGrid[iter->m_xPos - 1][iter->m_yPos + 1]->setPrevious(m_tileGrid[iter->m_xPos][iter->m_yPos]->m_xPos, m_tileGrid[iter->m_xPos][iter->m_yPos]->m_yPos);
			tileQueue.push_back(*m_tileGrid[iter->m_xPos - 1][iter->m_yPos + 1]);
			j++;
		}
		

		iter++;
		tileQueue.pop_front();
	}




}

/// <summary>
/// Calculates the optimal path through the flowfield
/// </summary>
/// <param name="m_startTile"></param>
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
/// Checks if a position that is passed in, is wihin the gameview
/// If it is true is returned 
/// If not false is returned 
/// </summary>
/// <param name="position"></param>
/// <param name="m_gameView"></param>
/// <returns></returns>
bool Grid::inView(sf::Vector2f position, sf::View &m_gameView)
{
	sf::Vector2f center = m_gameView.getCenter();
	float width = m_gameView.getSize().x / 2;
	float height = m_gameView.getSize().y / 2;

	if (position.x  < center.x + width && position.x + 120> center.x - width
		&& position.y  < center.y + height && position.y + 120 > center.y - height) {
		
			return true;
		
	}

	else
	{
		return false;
	}
}

/// <summary>
/// Renders all the tiles in the map only if they are in the game view
/// This will improve performance
/// </summary>
void Grid::render(sf::RenderWindow &window, sf::View &m_gameView, bool draw)
{
	for (int i = 0; i < m_gridSize; i++)
	{
		for (int j = 0; j < m_gridSize; j++)
		{

			if (inView(m_tileGrid[i][j]->m_position, m_gameView))
			{ 
				m_tileGrid[i][j]->render(window);
			}
			
		}

	}

}