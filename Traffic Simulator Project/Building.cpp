#include "stdafx.h"
#include "Building.h"

Building::Building()
{
	//Default constructor
	m_dimensions.set(0.f, 0.0f);
	m_position.set(0.0f, 0.0f);
	m_fOrientation = 0.0f;

	sf::RectangleShape * building = new sf::RectangleShape();
	building->setSize(sf::Vector2f(m_dimensions.x(), m_dimensions.y()));
	building->setOrigin(m_dimensions.x() / 2.0f, m_dimensions.y() / 2.0f);
	building->setPosition(m_position.x(), m_position.y());
	building->setRotation(-m_fOrientation);
	building->setFillColor(sf::Color::Green);
	m_renderShape = building;
	lane = 0;
	spawnLimit = 2;
	spawnTimer = spawnLimit;
	random = true;
}

Building::Building(Vector2D dimensions, Vector2D position, float orientation)
{
	//Constructor with parameters
	m_dimensions = dimensions;
	m_position = position;
	m_fOrientation = orientation;

	sf::RectangleShape * building = new sf::RectangleShape();
	building->setSize(sf::Vector2f(m_dimensions.x(), m_dimensions.y()));
	building->setOrigin(m_dimensions.x() / 2.0f, m_dimensions.y() / 2.0f);
	building->setPosition(m_position.x(), m_position.y());
	building->setRotation(-m_fOrientation);
	building->setFillColor(sf::Color::Green);

	m_renderShape = building;
	spawnLimit = 8;
	spawnTimer = spawnLimit;
	switch ((int)m_fOrientation)	//depending on orientation set lane at which the vehicle should be spawned
	{
	case 0: lane = -7; break;
	case 90: lane = 7; break;
	case 180: lane = 7; break;
	case 270: lane = -7; break;
	}
	random = true;
}

Vector2D Building::getDimensions()
{
	return m_dimensions;
}

int Building::getLane()
{
	return lane;
}

void Building::setColor()
{
	m_renderShape->setFillColor(sf::Color::Red);
}

void Building::setColor2()
{
	m_renderShape->setFillColor(sf::Color::Green);
}

float Building::getSpawnTimer()
{
	return spawnTimer;
}

float Building::getSpawnLimit()
{
	return spawnLimit;
}

void Building::setSpawnTimer(float time)
{
	spawnTimer = time;
}

void Building::setSpawnLimit(float time)	//increases or decreases spawn limit by the value sent from main upon button press
{
	spawnLimit = spawnLimit+time;
	spawnTimer = spawnLimit;
}

void Building::setConnectedInter(int inter)
{
	connectedInter = inter;
}

int Building::getConnectedInter()
{
	return connectedInter;
}

void Building::setGoal(int goal, bool rand)	//set target destination for this building
{
	random = rand;
	goalDestination = goal;

}

int Building::getGoal()	// get target destination for this building
{
	if (random)
	{
		goalDestination = rand() % buildingAmount;
	}

	return goalDestination;
}

void Building::setBuildingAmount(int amount)
{
	buildingAmount = amount;
}

bool Building::getIsRandom()
{
	return random;
}



