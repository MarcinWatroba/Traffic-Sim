#ifndef GRID_H
#define GRID_H

#include "Vector2D.h"
#include <iostream>
#include <vector>
#include "Car.h"
#include "Intersection.h"

class Grid
{
private:
	vector<pair<int, Vector2D>> boxes;	//ids and locations of each containers
	vector<pair<int, vector<int>>> containers;	// vector of ids and actual containers
	vector<int> container;	//vehicle container
	vector<pair<int, vector<int>>> interContainers;	//intersection container
	float cellSize;	//size of each container
	float cols;	//amount of container columns
	int n;
	float rows;	//amount of container rows
public:
	Grid();
	void fillIntersectionBoxes(Intersection intersection, int num);	//fill intersection boxes with intersections
	int fillBoxes(Car car, bool initial, int num, int box);	//fill vehicle containers with vehicles

	vector<int> getCointainer(int box, int iter);	// get particular container
	vector<int> getInterCointainer(int box, int iter);
	void clearBoxes();
};

#endif