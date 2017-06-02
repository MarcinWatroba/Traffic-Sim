#include "stdafx.h"
#include "PathPlanning.h"

PathPlanning::PathPlanning()
{
}

vector<vector<ConnectInter>> PathPlanning::calculatePaths(vector<Intersection> inters, vector<pair<int, Building>> builds)
{
	intersection = inters;	//intersections
	buildings = builds;	//buildings 


	for (auto it = buildings.begin(); it != buildings.end(); it++)	//for all starting positions/buildings
	{
		startPos = Vector2D(it->second.getPosition().x(), it->second.getPosition().y());	//get position of the starting building
		for (auto jt = buildings.begin(); jt != buildings.end(); jt++)	//for all goal positions/buildings
		{
			endPos = Vector2D(jt->second.getPosition().x(), jt->second.getPosition().y());	//get the position of the goal building.
			path.clear();	//clear path generated for last destination to generate new for the next destination/path finding iteration
			//clear all data for the next path finding iteration
			connections.clear();	
			connectionsIDs.clear();
			usedIDs.clear();
			openList.clear();
			closedList.clear();

			goalDist = 9999.f;	//initially set to high value,because later the program will need to check if the new goal distance is lower than the last one
			directionChosen = false;	//next direction in a path has not been chosen

			currentInter = intersection.at(it->second.getConnectedInter());	//intersection working on
			currentLocation = currentInter.getPosition();	//location of current intersection
			connectedObjects = currentInter.getConnectedLoc();	//connected positions direcitons and coords
			usedIDs.push_back(it->second.getConnectedInter());	//used intersection IDs
			lastID = make_pair(false, it->second.getConnectedInter());	//last used ID
			parentDistance = make_pair(make_pair(true, distance(buildings.begin(), it)), currentLocation.distance(endPos));	//parent ID and distance of the current position to destination
			id = lastID;
			closedList.insert(make_pair(id, parentDistance));	//insert the starting position into the closed list
			//connected positions IDs (loc in vector) and type (building, intersection) of the closest position, used to delete it so it will not be searched again
			connectedIDs = currentInter.getConnectedID();	//connected ids of current intersection


			checkClosestPath();	//get the shortest path to the goal


			path.push_back(closestLocation.first);	//push back the closest location



			currentLocation = buildings.at(closestID.second).second.getPosition();	//current location equals the destination location



			paths.push_back(path);	//push back the generated path to the vector of paths
		}
	}




	return paths;	//return all paths
}

void PathPlanning::checkClosestPath()
{
	bool end = false;	// the goal has not been found
	while (!end)	//while goal has not been found
	{
		goal = false;
		int iteration;
		goalDist = 99999.f;
		for (auto kt = connectedObjects.begin(); kt != connectedObjects.end();)	//for all connected objects
		{

			iteration = distance(connectedObjects.begin(), kt);	

			if (connectedIDs.at(iteration).first && kt->second.distance(endPos) > 0)	//if connected object is a building but not the goal, erase it from potential path.
			{

				connectedIDs.erase(connectedIDs.begin() + iteration);	
				kt = connectedObjects.erase(kt);


			}
			else
			{

				currentLocation = kt->second;	//else current location equals the connected location
				//current location id equals the id(iteration) of the connected intersection, and connected IDs equal connected IDs of connected intersection
				id = make_pair(connectedIDs.at(iteration).first, connectedIDs.at(iteration).second);
				// the parent of the current intersection becomes the last intersection, and the add the distance of the current location against end location to the current path distance
				parentDistance = make_pair(lastID, closedList.find(lastID)->second.second + currentLocation.distance(endPos)); 
				//open list insert current intersection and its path distance + end location distance
				openList.insert(make_pair(id, parentDistance));
				if (currentLocation.distance(endPos) == 0)	//if the current location is the end location insert it into closed list and save it as the end location
				{
					closedList.insert(make_pair(id, parentDistance));
					closedList.insert(make_pair(id, parentDistance));
					endLoc = make_pair(id.second, lastID.second);
					lastID = make_pair(connectedIDs.at(iteration).first, connectedIDs.at(iteration).second);

					goal = true;	//goal has been reached
					break;
				}

				kt++;
			}



		}
		if (!goal)	//if goal has not been reached
		{
			for (auto lt = openList.begin(); lt != openList.end(); lt++)	//check F score of the intersections in open list, find the lowest score and set it as current intersection
			{
				if (closedList.count(lt->first) == 0)
				{
					if (lt->second.second < goalDist)
					{
						goalDist = lt->second.second;
						lastID = lt->first;
						parentDistance = make_pair(lt->second.first, goalDist);
					}

				}
			}

			closedList.insert(make_pair(lastID, parentDistance));	//add the intersection with lowest f score to the closed list

			currentInter = intersection.at(lastID.second);	//intersection working on
			currentLocation = currentInter.getPosition();
			connectedObjects = currentInter.getConnectedLoc();	//connected positions direcitons and coords
			connectedIDs = currentInter.getConnectedID();	//connected ids of current intersection
			openList.erase(openList.find(lastID));	//erase the inter from open list
		}
		else
		{
			currentLocation = buildings.at(lastID.second).second.getPosition();	//if goal has been erached save current location as goal
		}

		if (currentLocation.distance(endPos) == 0)	//if reached destination
		{
			//calculate the path to the start position, add the required vehicle turn at each intersection to the path vector
			currentInter = intersection.at(endLoc.second);
			pair<bool, int> currentIntersection = closedList.rbegin()->second.first;
			connectedIDs = currentInter.getConnectedID();
			connectedObjects = currentInter.getConnectedLoc();
			currentLocation = buildings.at(endLoc.first).second.getPosition();	//set up end location and its parent
			for (auto lt = connectedIDs.begin(); lt != connectedIDs.end(); lt++)
			{
				if (lt->second == endLoc.first)
				{
					break;
				}
			}

			bool startBuilding = false;
			//while not reached start position, iteratively find next parent intersections until reached the start position and path vector is filled with turning data
			while (currentLocation.distance(startPos) != 0)	
			{


				connectedIDs = currentInter.getConnectedID();
				connectedObjects = currentInter.getConnectedLoc();
				currentLocation = currentInter.getPosition();


				for (auto lt = connectedIDs.begin(); lt != connectedIDs.end(); lt++)
				{
					if (*lt == closedList.find(currentIntersection)->second.first)
					{
						currentIntersection.first = lt->first;
						currentIntersection.second = lt->second;
						if (!lt->first)
						{
							currentInter = intersection.at(closedList.find(currentIntersection)->first.second);
						}
						path.push_back(connectedObjects.at(distance(connectedIDs.begin(), lt)).first);
						if (lt->first && connectedObjects.at(distance(connectedIDs.begin(), lt)).second.distance(startPos) == 0)
						{
							value = lt->second;
							startBuilding = true;
						}
						break;
					}
				}

				if (startBuilding)
				{
					break;
				}

			}
			if (currentIntersection.first)
			{
				currentLocation = buildings.at(value).second.getPosition();
			}
			end = true;
		}

	}
}
