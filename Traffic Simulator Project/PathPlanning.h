#ifndef PATHPLANNING_H
#define PATHPLANNING_H


#include <vector>
#include "Car.h"
#include "Intersection.h"
#include "Building.h"

class PathPlanning
{
private:
	vector<Intersection> intersection;
	vector<pair<int, Building>> buildings;
	vector<vector<ConnectInter>> paths;
	Vector2D startPos;
	Vector2D endPos;
	//endPos = jt->second.getPosition();
	float goalDist;
	bool directionChosen;
	Intersection currentInter;
	Vector2D currentLocation;
	vector<pair<ConnectInter, Vector2D>> connectedObjects;
	vector<ConnectInter> path;
	vector<pair<bool, int>> connectedIDs;
	vector<int> usedIDs;
	bool alreadyUsed;
	vector<vector<pair<ConnectInter, Vector2D>>> connections;
	vector<vector<pair<bool, int>>> connectionsIDs;
	pair<ConnectInter, Vector2D> closestLocation;	//position and coords of closest connected location
	pair<bool, int> closestID;	//ID and type of closest connected location
	int positionUsed;	//ID of the closest position, used to delete it so it will not be searched again
	int lastInter;
	bool building;
	bool erasePath;
	double simulationDuration;
	int parentID;
	pair<pair<bool, int>, float> parentDistance;
	//int id;
	pair<bool, int> id;
	pair<bool, int> lastID;
	bool goal;
	map<pair<bool, int>, pair<pair<bool, int>, float>> openList;
	map<pair<bool, int>, pair<pair<bool, int>, float>> closedList;
	pair<int, int> startLoc;
	pair<int, int> endLoc;
	int value;
	bool m_end;

public:
	PathPlanning();

	vector<vector<ConnectInter>> calculatePaths(vector<Intersection> inters, vector<pair<int, Building>> builds);
	void checkClosestPath();


};

#endif