#ifndef ROAD_H
#define ROAD_H

#include "Object.h"

class Road : public Object
{
private:
	Vector2D m_dimensions;
public:
	Road();
	Road(Vector2D dimensions, Vector2D position, float orientation);
	Vector2D getDimensions();
};

#endif