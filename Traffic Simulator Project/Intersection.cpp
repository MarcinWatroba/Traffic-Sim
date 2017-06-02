#include "stdafx.h"
#include "Intersection.h"

Intersection::Intersection()
{
	lStatus = RED_VERTICAL;
	m_dimensions.set(0.f, 0.0f);
	m_position.set(0.0f, 0.0f);
	m_fOrientation = 0.0f;

	hLightLimit = 10.f;
	vLightLimit = 10.f;

	hLightTimer = hLightLimit;
	vLightTimer = vLightLimit;

	m_setTLights = ALL;
	directionAmount = 0;
	sf::RectangleShape * intersection = new sf::RectangleShape();
	intersection->setSize(sf::Vector2f(m_dimensions.x(), m_dimensions.y()));
	intersection->setOrigin(m_dimensions.x() / 2.0f, m_dimensions.y() / 2.0f);
	intersection->setPosition(m_position.x(), m_position.y());
	intersection->setRotation(-m_fOrientation);
	intersection->setFillColor(sf::Color::Blue);
	m_renderShape = intersection;
}

Intersection::Intersection(Vector2D dimensions, Vector2D position, float orientation, bool west, bool east, bool north, bool south, bool highway)
{
	vehiclesPassed = 0;
	m_dimensions = dimensions;
	m_position = position;
	m_fOrientation = orientation;
	m_highway = highway;

	hLightLimit = 10.f;
	vLightLimit = 10.f;

	hLightTimer = hLightLimit;
	vLightTimer = vLightLimit;

	m_setTLights = ALL;

	directions.insert(pair<char,bool>('w', west));
	directions.insert(pair<char, bool>('e', east));
	directions.insert(pair<char, bool>('n', north));
	directions.insert(pair<char, bool>('s', south));
	directionAmount = 0;
	if (east)
		directionAmount++;
	if (west)
		directionAmount++;
	if (north)
		directionAmount++;
	if (south)
		directionAmount++;


	sf::RectangleShape * intersection = new sf::RectangleShape();
	intersection->setSize(sf::Vector2f(m_dimensions.x(), m_dimensions.y()));
	intersection->setOrigin(m_dimensions.x() / 2.0f, m_dimensions.y() / 2.0f);
	intersection->setPosition(m_position.x(), m_position.y());
	intersection->setRotation(-m_fOrientation);
	intersection->setFillColor(sf::Color::Blue);
	m_renderShape = intersection;

}

Vector2D Intersection::getDimensions()
{
	return m_dimensions;
}

void Intersection::lights(float timestep)
{
	//change traffic lights at (timestep) time
	switch (lStatus)
	{
	case GREEN_VERTICAL: setLights(YELLOW_VERTICAL);
		break;
	case YELLOW_VERTICAL:  setLights(RED_VERTICAL);	//set to red vertical, therefore green horizontal
		break;
	case RED_VERTICAL: setLights(YELLOW_HORIZONTAL);
		break;
	case YELLOW_HORIZONTAL:  setLights(GREEN_VERTICAL);	//set to green vertical, therefore red horizontal
		break;

	}
	if (vLightTimer < 0.)
	{
		vLightTimer = vLightLimit;
	}
	if (hLightTimer < 0.)
	{
		hLightTimer = hLightLimit;
	}

}

void Intersection::setLights(LightStatus lights)
{
	lStatus = lights;
}

LightStatus Intersection::getLights()
{
	return(lStatus);
}

void Intersection::stopCar(Car &car)	//function controlling traffic over the intersection
{
	Vector2D farDistance = m_dimensions + 15;
	Vector2D closeDistance = m_dimensions - 8;
	Vector2D checkDistance = m_dimensions - 7;

	carPos = car.getPosition();
	car.setBlockingFlow(false);
	car.setAtIntersection(false);
	car.loc = ROAD;
	car.status = MOVING;

	distance = carPos.distance(m_position);

	if (directionAmount > 2)	//if intersection has more than two directions
	{
		if ((distance < farDistance.y()) && carPos.y() > m_position.y() && car.getOrientation() == 180)	// if the vehicle is not too far away
		{

			car.setBlockingFlow(false);
			if (distance > closeDistance.y())
			{

				if (lStatus == RED_VERTICAL || YELLOW_VERTICAL)	//if lights are yellow or red vertical
				{
					car.setHorizontalWaiting(false);
					car.status = DECELERATING;	//decelerate
					if (distance < checkDistance.y() && lStatus == RED_VERTICAL)	//if lights are red vertical and distance is less than 23 units
					{
						car.loc = INTERSECTION;
						if (distance > closeDistance.y())
						{
							car.status = LIGHTS_WAITING;	//stop the car
						}
					}

				}
				if (lStatus == GREEN_VERTICAL)	//if lights are green vertical
				{
					car.setHorizontalWaiting(true);
					car.status = SLOWING_DOWN;	//car can move
					if (distance < checkDistance.y())
					{
						car.loc = INTERSECTION;
					}

				}
			}
			else if (carPos.x() > m_position.x() && (distance < m_dimensions.x() - 15))
			{
				car.setBlockingFlow(true);
			}

		}

		else if ((distance < farDistance.y()) && carPos.y() < m_position.y() && car.getOrientation() == 0)
		{
			car.setBlockingFlow(false);
			if (distance > closeDistance.y())
			{

				if (lStatus == RED_VERTICAL || YELLOW_VERTICAL)	//if lights are yellow or red vertical
				{
					car.setHorizontalWaiting(false);
					car.status = DECELERATING;	//decelerate
					if (distance < checkDistance.y() && lStatus == RED_VERTICAL)	//if lights are red vertical and distance is less than 23 units
					{
						car.loc = INTERSECTION;
						if (distance > closeDistance.y())
						{
							car.status = LIGHTS_WAITING;	//stop the car
						}
					}

				}
				if (lStatus == GREEN_VERTICAL)	//if lights are green vertical
				{
					car.setHorizontalWaiting(true);
					car.status = SLOWING_DOWN;	//car can move
					if (distance < checkDistance.y())
					{
						car.loc = INTERSECTION;
					}

				}
			}
			else if (carPos.x() < m_position.x() && (distance < m_dimensions.x() - 15))
			{
				car.setBlockingFlow(true);
			}

		}


		//if car is heading west and it's distance to intersection is less than 40 but higher than 15 units
		else if (distance < farDistance.x() && carPos.x() > m_position.x() && car.getOrientation() == 270)
		{

			car.setBlockingFlow(false);
			if (distance > closeDistance.x())
			{


				if (lStatus == GREEN_VERTICAL || YELLOW_HORIZONTAL) //if lights are yellow or green vertical (red horizontal)
				{
					car.setHorizontalWaiting(true);
					car.status = DECELERATING;	//decelerate
					if ((distance < checkDistance.x()) && lStatus == GREEN_VERTICAL)	//if lights are green vertical (red horizontal) and distance is less than 23 units
					{
						car.loc = INTERSECTION;

						if (distance > closeDistance.x())
						{
							car.status = LIGHTS_WAITING;	//stop the car
						}
					}

				}
				if (lStatus == RED_VERTICAL)	//if lights are red vertical (green horizontal)
				{
					car.setHorizontalWaiting(false);
					car.status = SLOWING_DOWN; // car can move
					if (distance < checkDistance.x())
					{
						car.loc = INTERSECTION;
					}

				}
			}
			else if (carPos.y() < m_position.y() && (distance < m_dimensions.y() - 15))
			{
				car.setBlockingFlow(true);
			}

		}

		//if car is heading east and it's distance to intersection is less than 40 but higher than 15 units
		else if (distance < farDistance.x() && carPos.x() < m_position.x() && car.getOrientation() == 90)
		{

			car.setBlockingFlow(false);
			if (distance > closeDistance.x())
			{
	
				if (lStatus == GREEN_VERTICAL || YELLOW_HORIZONTAL) //if lights are yellow or green vertical (red horizontal)
				{
					car.setHorizontalWaiting(true);
					car.status = DECELERATING;
					if ((distance < checkDistance.x()) && lStatus == GREEN_VERTICAL)	//if lights are green vertical (red horizontal) and distance is less than 23 units
					{
						car.loc = INTERSECTION;

						if (distance > closeDistance.x())
						{
							car.status = LIGHTS_WAITING;	//stop the car
						}
					}

				}
				if (lStatus == RED_VERTICAL)	//if lights are red vertical (green horizontal)
				{
					car.setHorizontalWaiting(false);
					car.status = SLOWING_DOWN;	// car can move
					if (distance < checkDistance.x())
					{
						car.loc = INTERSECTION;
					}

				}
			}
			else if (carPos.y() > m_position.y() && (distance < m_dimensions.y() - 15))
			{
				car.setBlockingFlow(true);
			}

		}
		if (car.getOrientation() == 270 || car.getOrientation() == 90)
		{
			if (distance < m_dimensions.x() + 5)
			{

				if (car.getSpeed() > 10)
				{
					car.loc = INTERSECTION;
				}
				else if (car.getSpeed() <= 10 && (distance < m_dimensions.x() - 8))
				{
					car.loc = INTERSECTION;
				}
				if (distance < m_dimensions.x() - 12)
				{
					car.setAtIntersection(true);
				}

			}
		}
		else
		{
			if (distance < m_dimensions.y() + 5)
			{

				if (car.getSpeed() > 10)
				{
					car.loc = INTERSECTION;
				}
				else if (car.getSpeed() <= 10 && (distance < m_dimensions.y()))
				{
					car.loc = INTERSECTION;
				}
				if (distance < m_dimensions.y())
				{
					car.setAtIntersection(true);
				}

			}
		}
	}
}

void Intersection::setConnectedLoc(ConnectInter direction, Vector2D position)
{
	connectedLocations.push_back(make_pair(direction, position));
}

void Intersection::setConnectedID(bool building, int ID)
{
	connectedID.push_back(make_pair(building, ID));
}

vector<pair<bool, int>> Intersection::getConnectedID()
{
	return connectedID;
}


vector<pair<ConnectInter, Vector2D>> Intersection::getConnectedLoc()
{
	return connectedLocations;
}

map<char, bool> Intersection::getDirections()
{
	return directions;
}

void Intersection::displayConnects()
{
	for (auto it = connectedLocations.begin(); it < connectedLocations.end(); it++)
	{
		if (it->first == NORTH)
		{
			std::cout << "NORTH:   ";
		}
		if (it->first == EAST)
		{
			std::cout << "EAST:   ";
		}
		if (it->first == WEST)
		{
			std::cout << "WEST:   ";
		}
		if (it->first == SOUTH)
		{
			std::cout << "SOUTH:   ";
		}
		std::cout << "x: " << it->second.x() << " y: " << it->second.y() << std::endl;
	}
}

void Intersection::setLightsTimer(TrafficLightsDirection setLights, float time)
{
	m_setTLights = setLights;
	switch (m_setTLights)
	{
	case ALL: setHLightLimit(time); setVLightLimit(time); break;
	case HORIZONTAL: setHLightLimit(time); break;
	case VERTICAL: setVLightLimit(time); break;
	default: break;
	}
}

void Intersection::setHLightTimer(float time)
{
	hLightTimer = time;
}

void Intersection::setVLightTimer(float time)
{
	vLightTimer = time;
}

float Intersection::getHorizontalTimer()
{
	return hLightTimer;
}

float Intersection::getVerticalTimer()
{
	return vLightTimer;
}

void Intersection::setHLightLimit(float time)
{
	hLightLimit = hLightLimit + time;
	hLightLimit = hLightLimit;
}

void Intersection::setVLightLimit(float time)
{
	vLightLimit = vLightLimit + time;
	vLightLimit = vLightLimit;
}

float Intersection::getHLimit()
{
	return hLightLimit;
}

float Intersection::getVLimit()
{
	return vLightLimit;
}

void Intersection::setVLightsIDs(int ID)
{
	vLightsIDs.push_back(ID);
}

void Intersection::setHLightsIDs(int ID)
{
	hLightsIDs.push_back(ID);
}

void Intersection::setColor()
{
	m_renderShape->setFillColor(sf::Color::Cyan);
}

void Intersection::setColor2()
{
	m_renderShape->setFillColor(sf::Color::Blue);
}

void Intersection::setColorGreen()
{
	m_renderShape->setFillColor(sf::Color::Green);
}

void Intersection::setColorRed()
{
	m_renderShape->setFillColor(sf::Color::Red);
}

vector<int> Intersection::getVLightsIDs()
{
	return 	vLightsIDs;
}

vector<int> Intersection::getHLightsIDs()
{
	return hLightsIDs;
}

void Intersection::setPassed(bool passed)
{
	m_passed = passed;
}

void Intersection::setPassedTime(double time)
{
	m_passedTime += time;
}

bool Intersection::getPassed()
{
	return false;
}

bool Intersection::getType()
{
	return m_highway;
}

int Intersection::getDirectionAmount()
{
	return directionAmount;
}

double Intersection::getPassedTime()
{
	return m_passedTime;
}
