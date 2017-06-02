#ifndef BUILDING_H
#define BUILDING_H

#include "Object.h"
#include "Car.h"
class Building : public Object
{
private:
	Vector2D m_dimensions;	//dimensions of a building
	int lane;	//lane at which vehicles will be spawned
	float spawnTimer;	//spawn timer calculating time till next spawn
	float spawnLimit;	//spawn limit, resets timer at the user set spawn limit after each spawn
	int connectedInter;	//connected intersection IDs
	int goalDestination;	//sets goal destination for the spawned cars
	bool random;	//sets goal destination to random	
	int buildingAmount;	//amount of buildings in the scene
public:
	Building();	
	Building(Vector2D dimensions, Vector2D position, float orientation);	//constructor with parameters
	
	//getter methods
	Vector2D getDimensions();
	int getLane();
	float getSpawnTimer();
	float getSpawnLimit();
	int getConnectedInter();
	int getGoal();
	bool getIsRandom();

	//setter methods
	void setColor();
	void setColor2();
	void setSpawnTimer(float time);
	void setSpawnLimit(float time);
	void setConnectedInter(int inter);
	void setGoal(int goal, bool rand);
	void setBuildingAmount(int amount);

};

#endif