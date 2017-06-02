#ifndef TRAFFICLIGHTS_H
#define TRAFFICLIGHTS_H

#include "Object.h"

enum LightColour {
	GREEN_COLOUR,	//green for vertical roads, therefore red for horizontal
	RED_COLOUR,	//red for vertical roads, therefore green for horizontal
	YELLOW_COLOUR
};



class TrafficLights : public Object
{
private:
	Vector2D m_dimensions;


public:
	TrafficLights();
	TrafficLights(Vector2D dimensions, Vector2D position, float orientation, LightColour colour);
	Vector2D getDimensions();
	LightColour lColour;	//traffic light status
	void setLights();
	void changeColour();

};

#endif