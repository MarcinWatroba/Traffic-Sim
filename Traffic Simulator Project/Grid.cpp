#include "stdafx.h"

#include "Grid.h"

Grid::Grid()
{
	cellSize = 100;

	cols = 2000 / cellSize;
	if (cols > (int)cols)
	{

		cols = (int)cols + 1;
	}
	else
	{
		cols = (int)cols;
	}
	rows = 3000 / cellSize;
	if (rows > (int)rows)
	{
		rows = (int)rows + 1;
	}
	else
	{
		rows = (int)rows;
	}
	n = 0;
	//for each column
	for (int i = 0; i < cols; i++)
	{
		for (int j = 0; j < rows; j++) //for each row of a column
		{
			boxes.push_back(make_pair(n, Vector2D(i * cellSize, j * cellSize)));	//add bucked ID and location pair vector to the boxes vector
			containers.push_back(make_pair(n, container));	//add bucket ID and vehicle container vector pair vector to
			interContainers.push_back(make_pair(n, container));	//add intersection container vector
			n++;

		}
	}

}

void Grid::fillIntersectionBoxes(Intersection intersection, int num)
{
	int i = 0;

	//int boxs = 0;
	float cx = intersection.getPosition().x();	//get intersection position
	float cy = intersection.getPosition().y();
	float x = 10000;
	float y = 10000;


	// if intersection is contained within a box add it to the container
	while (!(cx >= x && cy >= y && cx <= x + cellSize && cy <= y + cellSize))	
	{
		x = boxes.at(i).second.x();
		y = boxes.at(i).second.y();

		i++;


	}
	std::cout << i - 1 << std::endl;
	interContainers.at(i - 1).second.push_back(num);
}

int Grid::fillBoxes(Car car, bool initial, int num, int box)
{
		int i = 0;

		//int boxs = 0;
		float cx = car.getPosition().x();	//get car position
		float cy = car.getPosition().y();
		float x;
		float y;
		x = boxes.at(box).second.x();
		y = boxes.at(box).second.y();
		x = 10000;
		y = 10000;

		// if car is still in the same box, leave it in the same container, else find the new box it is in and add it to its respective container
		if (cx >= x && cy >= y && cx <= x + cellSize && cy <= y + cellSize)
		{
			containers.at(box).second.push_back(num);
			return box;
		}
		else
		{

			while (!(cx >= x && cy >= y && cx <= x + cellSize && cy <= y + cellSize))
			{
				x = boxes.at(i).second.x();
				y = boxes.at(i).second.y();

				i++;


			}

			containers.at(i - 1).second.push_back(num);
			return i - 1;

		}



}

vector<int> Grid::getCointainer(int box, int iter)	//get vehicle container and its surrounding containers for collision detection
{
	switch (iter)
	{
	case 0: 	if(box >= 0) return containers.at(box).second; break;
	case 1: 	if (box - 1 >= 0) return containers.at(box - 1).second;
				else return containers.back().second; break;
	case 2: 	if (box + 1 < n) return containers.at(box + 1).second;
				else return containers.back().second; break;
	case 3: 	if (box + rows - 1 < n) return containers.at(box + rows - 1).second;
				else return containers.back().second; break;
	case 4: 	if (box + rows < n) return containers.at(box + rows).second;
				else return containers.back().second; break;
	case 5: 	if (box + rows + 1 < n) return containers.at(box + rows + 1).second;
				else return containers.back().second; break;
	case 6: 	if (box - rows - 1 >= 0) return containers.at(box - rows - 1).second;
				else return containers.back().second;  break;
	case 7: 	if (box - rows >= 0) return containers.at(box - rows).second;
				else return containers.back().second; break;
	case 8: 	if (box - rows + 1 >= 0) return containers.at(box - rows + 1).second;
				else return containers.back().second; break;
	}

}

vector<int> Grid::getInterCointainer(int box, int iter)	//same as above but for intersections
{
	switch (iter)
	{
	case 0: 	return interContainers.at(box).second; break;
	case 1: 	if (box - 1 >= 0) return interContainers.at(box - 1).second;
				else return interContainers.back().second; break;
	case 2: 	if (box + 1 < n) return interContainers.at(box + 1).second;
				else return interContainers.back().second; break;
	case 3: 	if (box + rows - 1 < n) return interContainers.at(box + rows - 1).second;
				else return interContainers.back().second; break;
	case 4: 	if (box + rows < n) return interContainers.at(box + rows).second;
				else return interContainers.back().second; break;
	case 5: 	if (box + rows + 1 < n) return interContainers.at(box + rows + 1).second;
				else return interContainers.back().second; break;
	case 6: 	if (box - rows - 1 >= 0) return interContainers.at(box - rows - 1).second;
				else return interContainers.back().second;  break;
	case 7: 	if (box - rows >= 0) return interContainers.at(box - rows).second;
				else return interContainers.back().second; break;
	case 8: 	if (box - rows + 1 >= 0) return interContainers.at(box - rows + 1).second;
				else return interContainers.back().second; break;
	}
}

void Grid::clearBoxes()	// clear all container contents
{
	for (auto it = containers.begin(); it != containers.end();)
	{
		it->second.clear();
		it++;
	}
}
