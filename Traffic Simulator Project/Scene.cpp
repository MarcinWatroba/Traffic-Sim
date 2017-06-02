#include "stdafx.h"
#include "Scene.h"



Scene::Scene()	//Initialize scene with all objects
{


	shortestTimeDriving = 9999999.0;
	longestTimeDriving = 0.0;
	timeDriving = 0.0;
	simulationDuration = 0.0;
	//Create building objects
	//180 NORTH, 0 SOUTH, 90 EAST, 270 WEST
	buildings.push_back(make_pair(0, Building(Vector2D(40.f, 40.f), Vector2D(100.f, 300.f), 90.f)));
	buildings.push_back(make_pair(1, Building(Vector2D(40.f, 40.f), Vector2D(1400.f, 300.f), 270.f)));
	buildings.push_back(make_pair(2, Building(Vector2D(40.f, 40.f), Vector2D(400.f, 70.f), 0.f)));
	buildings.push_back(make_pair(3, Building(Vector2D(40.f, 40.f), Vector2D(400.f, 800.f), 180.f)));
	buildings.push_back(make_pair(4, Building(Vector2D(40.f, 40.f), Vector2D(1200.f, 70.f), 0.f)));
	buildings.push_back(make_pair(5, Building(Vector2D(40.f, 40.f), Vector2D(1200.f, 800.f), 180.f)));
	buildings.push_back(make_pair(6, Building(Vector2D(40.f, 40.f), Vector2D(100.f, 600.f), 90.f)));
	buildings.push_back(make_pair(7, Building(Vector2D(40.f, 40.f), Vector2D(1400.f, 600.f), 270.f)));
	buildings.push_back(make_pair(8, Building(Vector2D(40.f, 40.f), Vector2D(1800.f, 450.f), 270.f)));
	buildings.push_back(make_pair(9, Building(Vector2D(40.f, 40.f), Vector2D(100.f, 1000.f), 180.f)));
	buildings.push_back(make_pair(9, Building(Vector2D(40.f, 40.f), Vector2D(100.f, 800.f), 0.f)));


	m_spawnedAmount = 0;
	m_arrivedAmount = 0;
	timeDriving = 0;
	summedTimeDriving = 0;
	buildings.push_back(make_pair(9, Building(Vector2D(40.f, 40.f), Vector2D(100.f, 1500), 90.f)));
	buildings.push_back(make_pair(9, Building(Vector2D(40.f, 40.f), Vector2D(100.f, 2000.f), 90.f)));
	buildings.push_back(make_pair(9, Building(Vector2D(40.f, 40.f), Vector2D(500.f, 1200.f), 0.f)));
	buildings.push_back(make_pair(9, Building(Vector2D(40.f, 40.f), Vector2D(1000.f, 2200.f), 180.f)));

	//intersections, size, position, orientation, road west?, road east? road north? road south? highway?
	inter.push_back(Intersection(Vector2D(30.f, 30.f), Vector2D(400.f, 300.f), 0.f, true, true, true, true, false));
	inter.back().setLights(RED_VERTICAL);
	inter.push_back(Intersection(Vector2D(30.f, 30.f), Vector2D(400.f, 600.f), 0.f, true, true, true, true, false));
	inter.back().setLights(RED_VERTICAL);
	inter.push_back(Intersection(Vector2D(30.f, 30.f), Vector2D(1200.f, 300.f), 0.f, true, true, true, true, false));
	inter.back().setLights(RED_VERTICAL);
	inter.push_back(Intersection(Vector2D(30.f, 30.f), Vector2D(1200.f, 600.f), 0.f, true, true, true, true, false));
	inter.back().setLights(RED_VERTICAL);
	inter.push_back(Intersection(Vector2D(60.f, 30.f), Vector2D(800.f, 600.f), 0.f, true, true, false, true, true));
	inter.back().setLights(RED_VERTICAL);
	inter.push_back(Intersection(Vector2D(60.f, 30.f), Vector2D(800.f, 900.f), 0.f, true, true, true, false, true));
	inter.back().setLights(RED_VERTICAL);

	inter.push_back(Intersection(Vector2D(30.f, 30.f), Vector2D(1200.f, 450.f), 0.f, false, true, true, true, false));
	inter.back().setLights(RED_VERTICAL);
	inter.push_back(Intersection(Vector2D(60.f, 30.f), Vector2D(1500.f, 450.f), 0.f, true, true, false, true, true));
	inter.back().setLights(RED_VERTICAL);
	inter.push_back(Intersection(Vector2D(60.f, 30.f), Vector2D(1500.f, 900.f), 0.f, true, false, true, true, true));
	inter.back().setLights(RED_VERTICAL);
	inter.push_back(Intersection(Vector2D(60.f, 30.f), Vector2D(1500.f, 1500.f), 0.f, true, false, true, true, true));
	inter.back().setLights(RED_VERTICAL);
	inter.push_back(Intersection(Vector2D(60.f, 30.f), Vector2D(1500.f, 2000.f), 0.f, true, false, true, false, true));
	inter.back().setLights(RED_VERTICAL);
	inter.push_back(Intersection(Vector2D(30.f, 30.f), Vector2D(100.f, 900.f), 0.f, false, true, true, true, false));
	inter.back().setLights(RED_VERTICAL);
	inter.push_back(Intersection(Vector2D(30.f, 30.f), Vector2D(500.f, 1500.f), 0.f, true, true, true, false, false));
	inter.back().setLights(RED_VERTICAL);
	inter.push_back(Intersection(Vector2D(30.f, 30.f), Vector2D(1000.f, 2000.f), 0.f, true, true, false, true, false));
	inter.back().setLights(RED_VERTICAL);

	// find buildings and intersections connected to the current intersection
	for (auto it = inter.begin(); it != inter.end(); it++)
	{
	closestNorthDist = 99999.0f;
		closestWestDist = 99999.0f;
		closestEastDist = 99999.0f;
		closestSouthDist = 99999.0f;
		grid.fillIntersectionBoxes(*it, distance(inter.begin(), it));

		map<char, bool> connectedRoads = it->getDirections();

		for (auto jt = inter.begin(); jt != inter.end(); jt++)
		{
			newClosestDist = it->getPosition().distance(jt->getPosition());

			if (connectedRoads['n'] && newClosestDist < closestNorthDist && jt->getPosition().y() < it->getPosition().y() && jt->getPosition().x() == it->getPosition().x() && newClosestDist > 5.0f)
			{
				closestNorthDist = newClosestDist;
				northPos = jt->getPosition();
				northLoc = distance(inter.begin(), jt);
				buildingNorth = false;
			}
			if (connectedRoads['w'] && newClosestDist < closestWestDist && jt->getPosition().x() < it->getPosition().x() && jt->getPosition().y() == it->getPosition().y() && newClosestDist > 5.0f)
			{
				closestWestDist = newClosestDist;
				westPos = jt->getPosition();
				westLoc = distance(inter.begin(), jt);
				buildingWest = false;
			}
			if (connectedRoads['e'] && newClosestDist < closestEastDist && jt->getPosition().x() > it->getPosition().x() && jt->getPosition().y() == it->getPosition().y() && newClosestDist > 5.0f)
			{
				closestEastDist = newClosestDist;
				eastPos = jt->getPosition();
				eastLoc = distance(inter.begin(), jt);
				buildingEast = false;
			}
			if (connectedRoads['s'] && newClosestDist < closestSouthDist && jt->getPosition().y() > it->getPosition().y() && jt->getPosition().x() == it->getPosition().x() && newClosestDist > 5.0f)
			{
				closestSouthDist = newClosestDist;
				southPos = jt->getPosition();
				southLoc = distance(inter.begin(), jt);
				buildingSouth = false;
			}
		}
		for (auto jt = buildings.begin(); jt != buildings.end(); jt++)
		{
			newClosestDist = it->getPosition().distance(jt->second.getPosition());
			if (connectedRoads['n'] && newClosestDist < closestNorthDist && jt->second.getPosition().y() < it->getPosition().y() && jt->second.getPosition().x() == it->getPosition().x() && newClosestDist > 5.0f)
			{
				closestNorthDist = newClosestDist;
				northPos = jt->second.getPosition();
				northLoc = distance(buildings.begin(), jt);
				buildingNorth = true;
			}
			if (connectedRoads['w'] && newClosestDist < closestWestDist && jt->second.getPosition().x() < it->getPosition().x() && jt->second.getPosition().y() == it->getPosition().y() && newClosestDist > 5.0f)
			{
				closestWestDist = newClosestDist;
				westPos = jt->second.getPosition();
				westLoc = distance(buildings.begin(), jt);
				buildingWest = true;
			}
			if (connectedRoads['e'] && newClosestDist < closestEastDist && jt->second.getPosition().x() > it->getPosition().x() && jt->second.getPosition().y() == it->getPosition().y() && newClosestDist > 5.0f)
			{
				closestEastDist = newClosestDist;
				eastPos = jt->second.getPosition();
				eastLoc = distance(buildings.begin(), jt);
				buildingEast = true;
			}
			if (connectedRoads['s'] && newClosestDist < closestSouthDist && jt->second.getPosition().y() > it->getPosition().y() && jt->second.getPosition().x() == it->getPosition().x() && newClosestDist > 5.0f)
			{
				closestSouthDist = newClosestDist;
				southPos = jt->second.getPosition();
				southLoc = distance(buildings.begin(), jt);
				buildingSouth = true;
			}
		}
		float distance = 15.f;
		if (it->getType() == true)
		{
			distance = 30.f;
		}



		if (connectedRoads['n'])
		{


			roads.push_back(Road(Vector2D(it->getDimensions().x(), closestNorthDist - 32), Vector2D(it->getPosition().x(), it->getPosition().y() - (closestNorthDist / 2)), 180.f));
			it->setConnectedLoc(NORTH, northPos);
			it->setConnectedID(buildingNorth, northLoc);
			if (it->getDirectionAmount() > 2)
			{
				tLightsH.push_back(TrafficLights(Vector2D(it->getDimensions().x(), 2.f), Vector2D(it->getPosition().x(), it->getPosition().y() - it->getDimensions().y() / 2), 0.f, RED_COLOUR));
				it->setHLightsIDs(tLightsH.size() - 1);
			}
		}
		if (connectedRoads['s'])
		{


			roads.push_back(Road(Vector2D(it->getDimensions().x(), closestSouthDist - 32), Vector2D(it->getPosition().x(), it->getPosition().y() + (closestSouthDist / 2)), 0.f));
			it->setConnectedLoc(SOUTH, southPos);
			it->setConnectedID(buildingSouth, southLoc);
			if (it->getDirectionAmount() > 2)
			{
				tLightsH.push_back(TrafficLights(Vector2D(it->getDimensions().x(), 2.f), Vector2D(it->getPosition().x(), it->getPosition().y() + it->getDimensions().y() / 2), 0.f, RED_COLOUR));
				it->setHLightsIDs(tLightsH.size() - 1);
			}
		}
		if (connectedRoads['w'])
		{


			roads.push_back(Road(Vector2D(it->getDimensions().y(), closestWestDist - 32), Vector2D(it->getPosition().x() - (closestWestDist / 2), it->getPosition().y()), 270.f));
			it->setConnectedLoc(WEST, westPos);
			it->setConnectedID(buildingWest, westLoc);
			if (it->getDirectionAmount() > 2)
			{
				tLightsV.push_back(TrafficLights(Vector2D(it->getDimensions().y(), 2.f), Vector2D(it->getPosition().x() - it->getDimensions().x() / 2, it->getPosition().y()), 90.f, GREEN_COLOUR));
				it->setVLightsIDs(tLightsV.size() - 1);
			}
		}
		if (connectedRoads['e'])
		{

			roads.push_back(Road(Vector2D(it->getDimensions().y(), closestEastDist - 32), Vector2D(it->getPosition().x() + (closestEastDist / 2), it->getPosition().y()), 90.f));
			it->setConnectedLoc(EAST, eastPos);
			it->setConnectedID(buildingEast, eastLoc);
			if (it->getDirectionAmount() > 2)
			{
				tLightsV.push_back(TrafficLights(Vector2D(it->getDimensions().y(), 2.f), Vector2D(it->getPosition().x() + it->getDimensions().x() / 2, it->getPosition().y()), 90.f, GREEN_COLOUR));
			it->setVLightsIDs(tLightsV.size() - 1);
			}
		}




		it->displayConnects();
	}


	for (auto it = buildings.begin(); it != buildings.end(); it++)
	{
		float closestDist = 99999.0f;
		float newDist = 0;
		for (auto jt = inter.begin(); jt != inter.end(); jt++)
		{
			newDist = it->second.getPosition().distance(jt->getPosition());
			if (newDist < closestDist && it->second.getOrientation() == 90)
			{
				if (jt->getPosition().x() > it->second.getPosition().x() && jt->getPosition().y() == it->second.getPosition().y())
				{
					closestDist = newDist;
					it->second.setConnectedInter(distance(inter.begin(), jt));
				}
			}
			if (newDist < closestDist && it->second.getOrientation() == 270)
			{
				if (jt->getPosition().x() < it->second.getPosition().x() && jt->getPosition().y() == it->second.getPosition().y())
				{
					closestDist = newDist;
					it->second.setConnectedInter(distance(inter.begin(), jt));
				}
			}
			if (newDist < closestDist && it->second.getOrientation() == 180)
			{
				if (jt->getPosition().y() < it->second.getPosition().y() && jt->getPosition().x() == it->second.getPosition().x())
				{
					closestDist = newDist;
					it->second.setConnectedInter(distance(inter.begin(), jt));
				}
			}
			if (newDist < closestDist && it->second.getOrientation() == 0)
			{
				if (jt->getPosition().y() > it->second.getPosition().y() && jt->getPosition().x() == it->second.getPosition().x())
				{
					closestDist = newDist;
					it->second.setConnectedInter(distance(inter.begin(), jt));
				}
			}
		}
	}


	for (auto it = buildings.begin(); it != buildings.end(); it++)
	{
		it->second.setBuildingAmount(buildings.size());
	}
	paths = planPaths.calculatePaths(inter, buildings);

	int iterations;
	int iteration;
	for (auto it = roads.begin(); it < roads.end(); it++)
	{
		iterations = distance(roads.begin(), it);
		for (auto jt = roads.begin(); jt < roads.end(); jt++)
		{
			iteration = distance(roads.begin(), jt);
			if (iterations != iteration)
			{
				if (it->getPosition().x() == jt->getPosition().x() && it->getPosition().y() == jt->getPosition().y())
				{
					if (it != roads.end())
					{
						jt = roads.erase(it);
						it = roads.begin();
					}
				}
			}
		}
	}

	


}

void Scene::spawn(float timestep)
{
	//Spawn car objects every (timestep) seconds

	for (auto it = buildings.begin(); it < buildings.end(); it++)
	{
		float time = it->second.getSpawnTimer();
		time -= timestep;
		it->second.setSpawnTimer(time);

		if(time < 0.01)
		{
			int goals = 0;
			do
			{
				goals = static_cast<ConnectInter>(it->second.getGoal()); //get random goal for the next spawned car
			} while (goals == distance(buildings.begin(), it));
			Vector2D goalPosition = buildings.at(goals).second.getPosition();
			//dimensions - position - velocity - orientation - goal
			cars.push_back(make_pair(1, Car(Vector2D(10.f, 10.f), it->second.getPosition() + it->second.getLane(), 100.f, it->second.getOrientation()))); //create car at south location
			cars.back().second.setGoalPos(goalPosition); //set goal
			cars.back().second.setSpeed(50.f); //set speed
			cars.back().second.setCarbox(grid.fillBoxes(cars.back().second, true, cars.size() - 1, cars.back().second.getCarBox()));
			cars.back().second.setPath(paths.at(goals * buildings.size() + distance(buildings.begin(), it)));
			it->second.setSpawnTimer(it->second.getSpawnLimit());
			m_spawnedAmount++;

		}


	}

		
	if (cars.size() > 1500)	//delete cars once they pass the car limit
	{
		for (int i = 0; i < buildings.size(); i++)
		{
			cars.erase(cars.begin());
		}
	}
	//display amount of cars in console
}

pair<ObjectType,int> Scene::findMouseClick(float x, float y, bool changeColour)
{
	pair<ObjectType, int> obj;
	obj = make_pair(NOTHING, -1);
	for (auto it = buildings.begin(); it < buildings.end(); it++)
	{
		if(changeColour == true)
		it->second.setColor2();

		if (x < it->second.getPosition().x() + 15 && y < it->second.getPosition().y() + 15 && x > it->second.getPosition().x() - 15 && y > it->second.getPosition().y() - 15)
		{
			obj = make_pair(BUILDING, distance(buildings.begin(), it));
			it->second.setColor();

		}
	}

	for (auto it = inter.begin(); it < inter.end(); it++)
	{
		it->setColor2();
		if (x < it->getPosition().x() + 15 && y < it->getPosition().y() + 15 && x > it->getPosition().x() - 15 && y > it->getPosition().y() - 15)
		{
			obj = make_pair(INTERSECT, distance(inter.begin(), it));
			it->setColor();

		}
	}
	return obj;
}

pair<ObjectType, int> Scene::findMouseClickReport(float x, float y, bool changeColour)
{
	pair<ObjectType, int> obj;
	obj = make_pair(NOTHING, -1);
	for (auto it = buildings.begin(); it < buildings.end(); it++)
	{
		if (changeColour == true)
			it->second.setColor2();

		if (x < it->second.getPosition().x() + 15 && y < it->second.getPosition().y() + 15 && x > it->second.getPosition().x() - 15 && y > it->second.getPosition().y() - 15)
		{
			obj = make_pair(BUILDING, distance(buildings.begin(), it));
			it->second.setColor();

		}
	}

	for (auto it = inter.begin(); it < inter.end(); it++)
	{
		it->setColor2();
		if (x < it->getPosition().x() + 15 && y < it->getPosition().y() + 15 && x > it->getPosition().x() - 15 && y > it->getPosition().y() - 15)
		{
			obj = make_pair(INTERSECT, distance(inter.begin(), it));
			it->setColor();

		}
	}

	if(obj.second != lowestUsedID)
	inter.at(lowestUsedID).setColorGreen();

	if (obj.second != highestUsedID)
	inter.at(highestUsedID).setColorRed();
	return obj;
}


float Scene::getBuildingSpawn(int building)
{
	return buildings.at(building).second.getSpawnLimit();;
}

void Scene::setBuildingSpawn(int building, float time)
{
	buildings.at(building).second.setSpawnLimit(time);

}

void Scene::setBuildingGoal(int start, bool rand, int goal)
{
	buildings.at(start).second.setGoal(goal, rand);
}

void Scene::changeLights(float timestep)
{
	//light colour changing method
	for (auto it = inter.begin(); it != inter.end(); it++)
	{
		float time;
		vector<int> hIDs = it->getHLightsIDs();
		vector<int> vIDs = it->getVLightsIDs();

		if (it->getLights() == GREEN_VERTICAL || it->getLights() == YELLOW_VERTICAL)
		{
			time = it->getVerticalTimer();
			time -= timestep;
			it->setVLightTimer(time);


		}
		else if (it->getLights() == RED_VERTICAL || it->getLights() == YELLOW_HORIZONTAL)
		{
			time = it->getHorizontalTimer();
			time -= timestep;
			it->setHLightTimer(time);

		}
		if (time <= 2.1f && time > 1.8f && (it->getLights() == GREEN_VERTICAL || it->getLights() == RED_VERTICAL))
		{


			if (it->getLights() == GREEN_VERTICAL)
			{
				for (auto jt = hIDs.begin(); jt != hIDs.end(); jt++)
				{
					tLightsH.at(*jt).setLights();
				}
			}
			if (it->getLights() == RED_VERTICAL)
			{
				for (auto jt = vIDs.begin(); jt != vIDs.end(); jt++)
				{
					tLightsV.at(*jt).setLights();
				}
			}
			it->lights(lightsClock.getElapsedTime().asSeconds());


		}
		if (time <= 0.1f)
		{

			it->lights(lightsClock.getElapsedTime().asSeconds());

			for (auto jt = hIDs.begin(); jt != hIDs.end(); jt++)
			{
				tLightsH.at(*jt).setLights();
			}
			for (auto jt = vIDs.begin(); jt != vIDs.end(); jt++)
			{
				tLightsV.at(*jt).setLights();
			}
			lightsClock.restart();
		}
	}





	//if (lightsClock.getElapsedTime().asSeconds() > 8.f && (inter.back().getLights() == GREEN_VERTICAL || inter.back().getLights() == RED_VERTICAL))
	//{

	//	if (inter.back().getLights() == GREEN_VERTICAL)
	//	{
	//		for (auto it = tLightsH.begin(); it != tLightsH.end(); it++)
	//		{
	//			it->setLights();
	//		}
	//	}
	//	if (inter.back().getLights() == RED_VERTICAL)
	//	{
	//		for (auto it = tLightsV.begin(); it != tLightsV.end(); it++)
	//		{
	//			it->setLights();
	//		}
	//	}
	//	for (auto it = inter.begin(); it != inter.end(); it++)
	//	{
	//		it->lights(lightsClock.getElapsedTime().asSeconds());
	//	}

	//}
	//if (lightsClock.getElapsedTime().asSeconds() > 10.f)
	//{
	//	for (auto it = inter.begin(); it != inter.end(); it++)
	//	{
	//		it->lights(lightsClock.getElapsedTime().asSeconds());
	//	}
	//	for (auto it = tLightsH.begin(); it != tLightsH.end(); it++)
	//	{
	//		it->setLights();
	//	}
	//	for (auto it = tLightsV.begin(); it != tLightsV.end(); it++)
	//	{
	//		it->setLights();
	//	}
	//	lightsClock.restart();
	//}
}

pair<float,float> Scene::setAllBuildingSpawn(float time)
{
	//set spawning frequency for buildings
	float spawnLimit;
	pair<float, float> limits;
	limits = make_pair(999999.f, 0.f);
	for (auto it = buildings.begin(); it < buildings.end(); it++)
	{
		spawnLimit = it->second.getSpawnLimit();

		it->second.setColor();
		if (spawnLimit > 0.5 || time == 0.5)
		it->second.setSpawnLimit(time);

		spawnLimit = it->second.getSpawnLimit();
		if (spawnLimit < limits.first)
			limits.first = spawnLimit;
		if (spawnLimit > limits.second)
			limits.second = spawnLimit;
	}
	for (auto it = inter.begin(); it < inter.end(); it++)
	{
		it->setColor2();
	}

	return limits;
}

pair<float, float> Scene::setAllLightsTime(float time)
{
	//set light duration for all lights
	float lightLimit;
	pair<float, float> limits;
	limits = make_pair(999999.f, 0.f);
	for (auto it = inter.begin(); it < inter.end(); it++)
	{

		it->setColor();
		if ((it->getVLimit() > 3.0 && it->getHLimit() > 3.0) || time == 0.5)
		it->setLightsTimer(ALL, time);

		lightLimit = it->getVLimit();
		if (lightLimit < limits.first)
			limits.first = lightLimit;
		if (lightLimit > limits.second)
			limits.second = lightLimit;

		lightLimit = it->getHLimit();
		if (lightLimit < limits.first)
			limits.first = lightLimit;
		if (lightLimit > limits.second)
			limits.second = lightLimit;

	}
	for (auto it = buildings.begin(); it < buildings.end(); it++)
	{
		it->second.setColor2();
	}

	return limits;
}


void Scene::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	//draw all objects
	for (auto it = roads.begin(); it != roads.end(); it++)
	{
		target.draw(*it);
	}
	for (auto it = inter.begin(); it != inter.end(); it++)
	{
		target.draw(*it);
	}
	for (auto it = cars.begin(); it != cars.end(); it++)
	{
		target.draw(it->second);
	}
	for (auto it = buildings.begin(); it != buildings.end(); it++)
	{
		target.draw(it->second);
	}
	for (auto it = tLightsH.begin(); it != tLightsH.end(); it++)
	{
		target.draw(*it);
	}
	for (auto it = tLightsV.begin(); it != tLightsV.end(); it++)
	{
		target.draw(*it);
	}


}

void Scene::update(float timestep)	//update scene every (timestep) seconds
{
	//clear spatial hashing grid of all contents
	grid.clearBoxes();
	simulationDuration += timestep;
	//find bucket for each vehicle
	for (auto it = cars.begin(); it != cars.end(); it++)
	{
		it->second.setCarbox(grid.fillBoxes(it->second, false, distance(cars.begin(), it), it->second.getCarBox()));
	}




	//update cars
	for (auto it = cars.begin(); it != cars.end(); it++)
	{
		it->second.setTimeDriving(timestep);
		it->second.update(timestep);	//update location


		it->second.setColorTwo();

		for (int i = 0; i < 9; i++)	//for its box and surrounding boxes react to all intersections in the same bucket
		{
			container = grid.getInterCointainer(it->second.getCarBox(), i);

				for (auto jt = container.begin(); jt != container.end(); jt++)	// for intersection at the same container and surrounding containers
				{
					float distance = it->second.getPosition().distance(inter.at(*jt).getPosition());
					if (distance < 80)
					{
						inter.at(*jt).setPassedTime(timestep);	//calculates the amount of time vehicles spent on this intersection
						inter.at(*jt).stopCar(it->second);	//stops car on red lights
						it->second.setInterDist(distance);	//gets vehicle distance to intersection

						if (distance < 36)
						{
							if (!it->second.getDirectionChosen())
							{
								it->second.setGoal();	//get the turn for this intersection
								inter.at(*jt).setPassed(true);	//intersection was passed

							}
							it->second.turn(inter.at(*jt).getConnectedLoc(), inter.at(*jt).getPosition(), distance, inter.at(*jt).getType());	//turn the car at the intersection

						}
						if (distance > 40 && distance < 50)
						{

							it->second.setDirectionChosen(false);	//next intersection is not passed


						}
					}
				}

		}

		//for each vehicle, check if there's vehicle in front of it, if it hasn't already detected vehicle
		if (it->second.status != QUEUE_WAITING)
		{
			for (int i = 0; i < 9; i++)
			{
				container = grid.getCointainer(it->second.getCarBox(), i);
				for (auto jt = container.begin(); jt != container.end(); jt++)
				{

					it->second.react(cars.at(*jt).second);	//if car is not waiting in the queue vehicle should react to other vehicles.

				}
			}

		}
		it->second.setBlockingTime(timestep);	//set vehicle blocking time at intersection
		//for each vehicle, if it's waiting at the lights or in a queue, set it's speed to zero
		if (it->second.status == LIGHTS_WAITING || it->second.status == QUEUE_WAITING)
		{
			it->second.setSpeed(0.0f);	
		}
		//decelerate if car in front or stopping
		if (it->second.status == DECELERATING)
		{
			if (it->second.getSpeed() > 0.f)
				it->second.setSpeed(it->second.getSpeed() - 0.6f);
			if (it->second.getSpeed() < 0.f)	//if it's speed is negative, set it to zero
				it->second.setSpeed(0.0f);

		}
		//slow down before intersection
		else if (it->second.status == SLOWING_DOWN)
		{
			if (it->second.getSpeed() > 25.f)
				it->second.setSpeed(it->second.getSpeed() - 0.6f);
			if (it->second.getSpeed() < 25.f)	//if it's speed is negative, set it to zero
				it->second.setSpeed(25.0f);

		}
		//else if not decelrating or waiting in queue, keep moving
		else if (it->second.status != LIGHTS_WAITING && it->second.status != QUEUE_WAITING)
		{
			if (it->second.getSpeed() < 50.f)
				it->second.setSpeed(it->second.getSpeed() + 0.4f);
		}

		//this stops car from moving if it has detected traffic in front
		it->second.status = TRAFFIC_DETECTED;

		//if car has reached it's destination, delete it
		if (it->second.checkGoal() == true)	//check if car reached its goal and update simulation statisics
		{
			m_arrivedAmount++;
			timeDriving = it->second.getTimeDriving();
			summedTimeDriving += timeDriving;
			if (timeDriving < shortestTimeDriving)
			{
				shortestTimeDriving = timeDriving;
			}
			if (timeDriving > longestTimeDriving)
			{
				longestTimeDriving = timeDriving;
			}

			if (it != cars.end())
			{

				grid.clearBoxes();
				cars.erase(it);
				it = cars.begin();
			}
		}
		Vector2D position = it->second.getPosition();

		if (position.x() < 50 || position.x() > 1900|| position.y() > 2400 || position.y() < 50 || it->second.getBlocking())	//check if vehicle is exiting the map(bug)
		{
			if (it != cars.end())
			{
				grid.clearBoxes();
				cars.erase(it);
				it = cars.begin();

			}
		}

	}

}

void Scene::getIntersectionPasses()
{
	//get the highest and lowest used intersection
	double lowestTime = 9999999;
	double highestTime = 1;
	lowestUsedID = 0;
	highestUsedID = 0;

	for (auto it = inter.begin(); it != inter.end(); it++)
	{
		if (it->getPassedTime() < lowestTime)
		{
			lowestTime = it->getPassedTime();
			lowestUsedID = distance(inter.begin(), it);
		}
		if (it->getPassedTime() > highestTime)
		{
			highestTime = it->getPassedTime();
			highestUsedID = distance(inter.begin(), it);
		}
	}


	inter.at(lowestUsedID).setColorGreen();

	inter.at(highestUsedID).setColorRed();



}

void Scene::setLightsH(int intersect, float time)
{
	inter.at(intersect).setHLightLimit(time);
}

void Scene::setLightsTime(TrafficLightsDirection setLights, int intersect, float time)
{
	inter.at(intersect).setLightsTimer(setLights, time);
}

void Scene::setLightsV(int intersect, float time)
{
	inter.at(intersect).setVLightLimit(time);
}

float Scene::getLightsH(int intersect)
{
	return inter.at(intersect).getHLimit();
}

float Scene::getLightsV(int intersect)
{
	return inter.at(intersect).getVLimit();
}

bool Scene::getIsBuildingRandom(int id)
{
	return buildings.at(id).second.getIsRandom();
}

unsigned int Scene::getVehSize()
{
	return cars.size();
}



double Scene::getShortestTimeDriving()
{
	return shortestTimeDriving;
}

double Scene::getLongestTimeDriving()
{
	return longestTimeDriving;
}

double Scene::getSummedTimeDriving()
{
	return summedTimeDriving;
}

double Scene::getSimulationDuration()
{
	return simulationDuration;
}

unsigned int Scene::getSpawnedAmount()
{
	return m_spawnedAmount;
}

unsigned int Scene::getArrivedAmount()
{
	return m_arrivedAmount;
}

void Scene::setIsEnd(bool end)
{
	m_end = end;
}