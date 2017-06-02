#ifndef SCENE_H
#define SCENE_H

#include <SFML/Graphics.hpp>


#include "Car.h"
#include "Intersection.h"
#include "TrafficLights.h"
#include "Building.h"
#include "Road.h"
#include "Grid.h"
#include "PathPlanning.h"
#include <math.h>


enum ObjectType {
	BUILDING,
	INTERSECT,
	NOTHING
};

class Scene : public sf::Drawable
{
private:

	int lol;
	Grid grid;
	PathPlanning planPaths;
	//Building objects

	vector<pair<int, Building>> buildings;
	//Road objects

	//vector of car objects
	vector<pair<int, Car>> cars;
	//intersection object
	vector<Intersection> inter;
	vector<TrafficLights> tLightsH;
	vector<TrafficLights> tLightsV;
	vector<Road> roads;
	vector<int> container;
	//clock used for changing traffic lights
	sf::Clock lightsClock;
	float closestNorthDist;
	float closestWestDist;
	float closestEastDist;
	float closestSouthDist;
	float newClosestDist;
	Vector2D northPos;
	Vector2D westPos;
	Vector2D eastPos;
	Vector2D southPos;
	int northLoc;
	int westLoc;
	int southLoc;
	int eastLoc;
	int lowestUsedID;
	int highestUsedID;
	bool buildingNorth;
	bool buildingWest;
	bool buildingEast;
	bool buildingSouth;
	unsigned int m_spawnedAmount;
	unsigned int m_arrivedAmount;
	double timeDriving;
	double shortestTimeDriving;
	double longestTimeDriving;
	double summedTimeDriving;

	vector<vector<ConnectInter>> paths;

	bool erasePath;
	double simulationDuration;

	int value;
	bool m_end;

public:
	Scene();
	void draw(sf::RenderTarget &target, sf::RenderStates states) const; //drawing all objects in the scene
	void update(float timestep); //updating all objects in the scene every (timestep) second
	void spawn(float timestep);	//spawning vehicles every (timestep) second
	void changeLights(float timestep);
	pair<ObjectType, int> findMouseClick(float x, float y, bool changeColour);
	pair<ObjectType, int> findMouseClickReport(float x, float y, bool changeColour);
	float getBuildingSpawn(int building);

	void setBuildingSpawn(int building, float time);
	void setBuildingGoal(int start, bool rand, int goal);
	void setLightsH(int intersect, float time);
	void setLightsTime(TrafficLightsDirection setLights, int intersect, float time);
	void setLightsV(int intersect, float time);
	float getLightsH(int intersect);
	float getLightsV(int intersect);
	pair<float, float> setAllBuildingSpawn(float time);
	pair<float, float> setAllLightsTime(float time);

	bool getIsBuildingRandom(int id);

	double getShortestTimeDriving();
	double getLongestTimeDriving();
	double getSummedTimeDriving();
	double getSimulationDuration();
	unsigned int getSpawnedAmount();
	unsigned int getArrivedAmount();

	void getIntersectionPasses();
	unsigned int getVehSize();
	void setIsEnd(bool end);


};

#endif
