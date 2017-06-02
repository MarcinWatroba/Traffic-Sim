#include "stdafx.h"
#include "Car.h"


Car::Car()
{
	m_dimensions.set(0.f, 0.0f);
	m_position.set(0.0f, 0.0f);
	m_fOrientation = 0.0f;
	m_speed = 0.f;
	carBox = 0;


	sf::RectangleShape * car = new sf::RectangleShape();
	car->setSize(sf::Vector2f(m_dimensions.x(), m_dimensions.y()));
	car->setOrigin(m_dimensions.x() / 2.0f, m_dimensions.y() / 2.0f);
	car->setPosition(m_position.x(), m_position.y());
	car->setRotation(-m_fOrientation);
	car->setFillColor(sf::Color::Magenta);
	m_renderShape = car;
	directionChosen = false;
	turnNum = 0;
}

Car::Car(Vector2D dimensions, Vector2D position, float speed, float orientation)
{

	m_dimensions = dimensions;
	m_position = position;
	m_fOrientation = orientation;
	carBox = 0;

	sf::RectangleShape * car = new sf::RectangleShape();
	car->setSize(sf::Vector2f(m_dimensions.x(), m_dimensions.y()));
	car->setOrigin(m_dimensions.x() / 2.0f, m_dimensions.y() / 2.0f);
	car->setPosition(m_position.x(), m_position.y());
	car->setRotation(-m_fOrientation);
	car->setFillColor(sf::Color::Magenta);
	m_renderShape = car;
	directionChosen = false;
	blockingFlow = false;
	turnNum = 0;
}

Vector2D Car::getDimensions()
{
	return m_dimensions;
}


void Car::setSpeed(float speed)
{
	m_speed = speed;
}

void Car::react(Car &car2)	//function responsible for vehicle reaction to other traffic
{

	car2Pos = car2.getPosition();
	car2goal = car2.getGoal();
	car2heading = car2.getOrientation();
	lowerBoundary = car2Pos - 6;	//lower boundary of detection i.e. the furthermost left the car will check for other vehicles based on it's orientation
	higherBoundary = car2Pos + 6;	//higher boundary of detection i.e. the furthermost right the car will check for other vehicles based on it's orientation
	lowerBoundaryInter = car2Pos - 20;	//lower boundary of detection i.e. the furthermost left the car will check for other vehicles based on it's orientation
	higherBoundaryInter = car2Pos + 20;	//higher boundary of detection i.e. the furthermost right the car will check for other vehicles based on it's orientation


	// if car is going north, and is going up on the highway, and it's goal is north but next goal eas, turn the vehicle right until it has changed lane
	if (m_fOrientation == 180 && onHighwayUp == true && goal == NORTH && nextGoal == EAST && m_position.x() < lastInter.x() + 21 && m_position.y() < lastInter.y() - 30 && !changedLine)
	{
		m_fOrientation -= 8;
	}
	else if (onHighwayUp == true && nextGoal == EAST && m_position.x() > lastInter.x() + 20 && m_position.x() < lastInter.x() + 22)	//if on the right lane, notify that the lane has been changed
	{
		m_fOrientation = 180;
		changedLine = true;
	}
	if (m_fOrientation == 0 && onHighwayDown == true && goal == SOUTH && nextGoal == WEST && m_position.x() > lastInter.x() - 21 && m_position.y() > lastInter.y() + 30 && !changedLine)	// same as above but for going south
	{
		m_fOrientation -= 8;
	}
	else if (onHighwayDown == true && nextGoal == WEST && m_position.x() < lastInter.x() - 20 && m_position.x() > lastInter.x() - 22)
	{
		m_fOrientation = 0;
		changedLine = true;
	}


	if (m_fOrientation == 180)	//if car is heading north
	{
		//if this car is within the bounds of intersection (intersection and surrounding area) and another car is within the bounds of the itnersection...
		//if this car goal is west and heading of the other car is not north, if this car is not blocking the flow
		if (car2.loc == INTERSECTION && loc == INTERSECTION && (goal == WEST) && (car2heading != 180) && blockingFlow == false)
		{
			//if the other car is position is close to the front or close one lane to the left
			if (car2Pos.y() < m_position.y() - 5 && m_position.x() > car2Pos.x() && m_position.x() < higherBoundaryInter.x())
			{
				//if the other car heading is south or west, (going straight or turning right) give way
				if ((car2.goal == SOUTH || car2.goal == WEST) && car2.distToInter < distToInter)
				{
					status = QUEUE_WAITING;

					wait = true;
				}
				else if (car2.getWait() == false && car2.goal == EAST &&  car2.distToInter < distToInter)	//else check which vehicle is closer to the intersection, give way to the closer veh
				{
					status = QUEUE_WAITING;

					wait = true;
				}

			}
		}
		if ((car2Pos.y() > (m_position.y() - 35) && (car2Pos.y() < m_position.y() - 5)) && m_position.x() > lowerBoundary.x())	// if the other car position is close in front
		{
			//if not blocking flow and car is at the same lane or one lane to the left and other car heading is south (straight) and other car is not waiting and is within bounds of intersection
			if (!blockingFlow && m_position.x() < higherBoundaryInter.x() && car2heading == 0 && goal == WEST && !car2.getWait() && car2.loc == INTERSECTION)
			{
				wait = true;	//give way to the car

				status = QUEUE_WAITING;
			}
			else if(m_position.x() < higherBoundary.x())	//else if the other vehicle is at the same lane
			{
				wait = false;
				if (m_speed > car2.getSpeed())	// if this car speed is higher than other car speed, decrease this cars speed
					m_speed = m_speed - 0.6f;
				//if the other car has the same heading as this car and is in front of this car and is turning west, and both cars are in the middle of intersection, wait
				if (car2heading == m_fOrientation && car2.goal == WEST && car2.atIntersection && atIntersection)
				{
					wait = true;
					status = QUEUE_WAITING;
				}
				if (car2Pos.y() > (m_position.y() - 12))	//completely stop car if it detects vehicle 12 units in front
				{

					wait = true;
					status = QUEUE_WAITING;
				}
			}

		}
	}
	else if (m_fOrientation == 0)	//if car is heading south
	{
		//same as above but different directions
		if (car2.loc == INTERSECTION && loc == INTERSECTION && (goal == EAST) && blockingFlow == false && (car2heading == 180 || car2heading == 270 || car2heading == 90))
		{

			if (car2Pos.y() > m_position.y() + 5 && m_position.x() > lowerBoundaryInter.x() && m_position.x() < car2Pos.x())
			{
				if ((car2.goal == NORTH || car2.goal == EAST) && car2.distToInter < distToInter)
				{
					status = QUEUE_WAITING;
					wait = true;
				}
				else if (car2.getWait() == false && car2.goal == WEST &&  car2.distToInter < distToInter)
				{
					status = QUEUE_WAITING;
					wait = true;
				}
			}
		}
		if ((car2Pos.y() < (m_position.y() + 35) && (car2Pos.y() > m_position.y() + 5)) && m_position.x() < higherBoundary.x())
		{

			if (!blockingFlow && m_position.x() > lowerBoundaryInter.x() && car2heading == 180 && goal == EAST && !car2.getWait() && car2.loc == INTERSECTION)
			{
				wait = true;
				status = QUEUE_WAITING;
			}
			else if(m_position.x() > lowerBoundary.x())
			{
				wait = false;
				if (m_speed > car2.getSpeed())
					m_speed = m_speed - 0.6f;

				if (car2heading == m_fOrientation && car2.goal == EAST && car2.atIntersection && atIntersection)
				{

		
					wait = true;
					status = QUEUE_WAITING;
				}

				if (car2Pos.y() < (m_position.y() + 12))	//stop car if it detects vehicle 12 units in front
				{
					wait = true;
					status = QUEUE_WAITING;
				}
			}

		}
	}
	else if (m_fOrientation == 270)	//if car is heading west
	{
		//same as above but different directions
		if (car2.loc == INTERSECTION && loc == INTERSECTION && (goal == SOUTH) && blockingFlow == false && (car2heading == 90 || car2heading == 180 || car2heading == 0))
		{
			if (car2Pos.x() < m_position.x() - 5 && m_position.y() > lowerBoundaryInter.y() && m_position.y() < car2Pos.y())
			{
				if ((car2.goal == EAST || car2.goal == SOUTH) && car2.distToInter < distToInter)
				{
					status = QUEUE_WAITING;
					wait = true;
				}
				else if (car2.getWait() == false && car2.goal == NORTH &&  car2.distToInter < distToInter)
				{
					status = QUEUE_WAITING;
					wait = true;
				}
			}
		}
		 if ((car2Pos.x() > (m_position.x() - 35) && (car2Pos.x() < m_position.x() - 5)) && m_position.y() < higherBoundary.y())
		{

			if (!blockingFlow && m_position.y() > lowerBoundaryInter.y() && car2heading == 90 && goal == SOUTH && !car2.getWait() && car2.loc == INTERSECTION)
			{
				wait = true;
				status = QUEUE_WAITING;
			}
			else if (m_position.y() > lowerBoundary.y())
			{
				wait = false;
				if (m_speed > car2.getSpeed())
					m_speed = m_speed - 0.6f;
				if (car2heading == m_fOrientation && car2.goal == SOUTH && car2.atIntersection && atIntersection)
				{

					wait = true;
					status = QUEUE_WAITING;
				}
				if (car2Pos.x() > (m_position.x() - 12))
				{
					wait = true;
					status = QUEUE_WAITING;

				}
			}
		}
	}
	else if (m_fOrientation == 90)	//if car is heading east
	{
		//same as above but different directions
		if (car2.loc == INTERSECTION && loc == INTERSECTION && (goal == NORTH) && blockingFlow == false && (car2heading == 270 || car2heading == 0 || car2heading == 180))
		{
			if (car2Pos.x() > m_position.x() + 5 && m_position.y() > car2Pos.y() && m_position.y() < higherBoundaryInter.y())
			{
				if ((car2.goal == WEST || car2.goal == NORTH) && car2.distToInter < distToInter)
				{
					status = QUEUE_WAITING;
					wait = true;
				}
				else if (car2.getWait() == false && car2.goal == SOUTH &&  car2.distToInter < distToInter)
				{
					status = QUEUE_WAITING;
					wait = true;
				}
			}
		}
		if ((car2Pos.x() < (m_position.x() + 35) && (car2Pos.x() > m_position.x() + 5)) && m_position.y() > lowerBoundary.y())
		{

			if (!blockingFlow && m_position.y() < higherBoundaryInter.y() && car2heading == 270 && goal == NORTH && !car2.getWait() && car2.loc == INTERSECTION)
			{
				wait = true;
				status = QUEUE_WAITING;
			}
			else if (m_position.y() < higherBoundary.y())
			{
				wait = false;
				if (m_speed > car2.getSpeed())
					m_speed = m_speed - 0.6f;
				if (car2heading == m_fOrientation && car2.goal == NORTH && car2.atIntersection && atIntersection)
				{
					wait = true;
					status = QUEUE_WAITING;
				}
				if (car2Pos.x() < (m_position.x() + 12))
				{
					wait = true;
					status = QUEUE_WAITING;

				}
			}
		}
	}



	if (status == TRAFFIC_DETECTED)	//prevents car from standing still after the vehicle in front drove away
	{
		status = MOVING;
	}



}

void Car::turn(vector<pair<ConnectInter, Vector2D>> interPos, Vector2D interPos2, float distance, bool highway)	//turn car at intersection towards its goal
{

	lastInter = interPos2;
	onHighwayUp = false;
	onHighwayDown = false;
	float laneMax = 9;
	float laneMin = 6;
	if (highway)	//if on highway and taking a right turn the position at which the vehicle should turn is changed
	{
		if (goal == NORTH)
		{
			onHighwayUp = true;
			if (nextGoal == EAST)
			{
				laneMin = 20;
				laneMax = 23;
			}
		}
		else if (goal == SOUTH)
		{
			onHighwayDown = true;
			if (nextGoal == WEST)
			{
				laneMin = 20;
				laneMax = 23;
			}
		}
		if (m_fOrientation == 0 && goal == WEST)
		{
			laneMin = 20;
			laneMax = 23;
		}
		else if (m_fOrientation == 180 && goal == EAST)
		{
			laneMin = 20;
			laneMax = 23;
		}
	}


	//if the car is at upper right side of the intersection
	if ((m_position.x() > interPos2.x() + laneMin && m_position.x() < interPos2.x() + laneMax) && (m_position.y() < interPos2.y() -6 && m_position.y() > interPos2.y() - 9))
	{
		if (goal == NORTH)
		{
			if (highway)
			onHighwayUp = true;
			m_fOrientation = 180;	//turn car towards north
		}
		if (goal == WEST)
		{
			m_fOrientation = 270;	//turn car towards west
		}

		changedLine = false;
	}

	//if the car is at lower right side of the intersection
	if ((m_position.x() > interPos2.x() + laneMin && m_position.x() < interPos2.x() + laneMax) && (m_position.y() > interPos2.y() +6 && m_position.y() < interPos2.y() + 9))
	{
		if (goal == NORTH)
		{
			if (highway)
			onHighwayUp = true;
			m_fOrientation = 180;	//turn car towards north
		}
		if (goal == EAST)
		{

			m_fOrientation = 90;	//turn car towards east
		}

		changedLine = false;
	}
	//lower left part of the intersection
	if ((m_position.x() < interPos2.x() - laneMin && m_position.x() > interPos2.x() - laneMax) && (m_position.y() > interPos2.y() +6 && m_position.y() < interPos2.y() + 9))
	{

		if (goal == EAST)
		{

			m_fOrientation = 90;	// turn towards east
		}
		if (goal == SOUTH)
		{
			if (highway)
			onHighwayDown = true;
			m_fOrientation = 0;
		}

		changedLine = false;
	}

	//upper left part of the intersection
	if ((m_position.x() < interPos2.x() - laneMin && m_position.x() > interPos2.x() - laneMax) && (m_position.y() < interPos2.y() -6 && m_position.y() > interPos2.y() -9))
	{

		if (goal == WEST)
		{

			m_fOrientation = 270;
		}
		if (goal == SOUTH)
		{
			if (highway)
			onHighwayDown = true;

			m_fOrientation = 0;
		}

			changedLine = false;
	}
}

ConnectInter Car::getGoal()
{
	return goal;
}


void Car::setGoalPos(Vector2D pos)
{
	goalLoc = pos;
}

Vector2D Car::getGoalLoc()
{
	return goalLoc;
}

//check if car has arrived at its destination point
bool Car::checkGoal()
{
	if ((m_position.x() < goalLoc.x() + 10 && m_position.x() > goalLoc.x() - 10) && (m_position.y() < goalLoc.y() + 10 && m_position.y() > goalLoc.y() - 10))
	{
		return true;
	}
	else
		return false;
}

int Car::getCarBox()
{
	return carBox;
}

void Car::setCarbox(int box)
{
	carBox = box;
}

void Car::setColorOne()
{
	m_renderShape->setFillColor(sf::Color::Red);
}

void Car::setColorTwo()
{
	m_renderShape->setFillColor(sf::Color::Magenta);
}

void Car::setDirectionChosen(bool chosen)
{
	directionChosen = chosen;
}

bool Car::getDirectionChosen()
{
	return directionChosen;
}

bool Car::getAtIntersection()
{
	return atIntersection;
}

void Car::setAtIntersection(bool inter)
{
	atIntersection = inter;
}

void Car::setBlockingFlow(bool blocking)
{
	blockingFlow = blocking;
}

bool Car::getWait()
{
	return wait;
}

void Car::setHorizontalWaiting(bool hWaiting)
{
	horizontalWaiting = hWaiting;
}

void Car::setPath(vector<ConnectInter> paths)
{
	path = paths;
}

void Car::setTimeDriving(double time)
{
	timeDriving += time;
}

double Car::getTimeDriving()
{
	return timeDriving;
}

void Car::setGoal()
{

	//increment path iterator for the next turn
	if (path.size() > 0 && turnNum < path.size())
	{
		goal = path.at(turnNum);
	}

	if (path.size() > 1 && turnNum + 1 < path.size())
	{
		nextGoal = path.at(turnNum + 1);
	}


		turnNum++;


	directionChosen = true;

}

void Car::setInterDist(float dist)
{
	distToInter = dist;
}

void Car::setBlockingTime(float time)
{
	if (m_speed < 10 && atIntersection == true)
	{
		blockingTime += time;
	}
	else
	{
		blockingTime = 0.f;
	}
}

bool Car::getBlocking()
{
	if (blockingTime > 30 && atIntersection == true)
	{
		return true;
	}
	return false;
}
