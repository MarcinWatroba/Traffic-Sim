#ifndef INTERSECTION_H
#define INTERSECTION_H

#include "Object.h"
#include "Car.h"
#include <unordered_set>

enum LightStatus {
	GREEN_VERTICAL,	//green for vertical roads, therefore red for horizontal
	RED_VERTICAL,	//red for vertical roads, therefore green for horizontal
	YELLOW_VERTICAL,
	YELLOW_HORIZONTAL
};
//used for setting traffic lights duration
enum TrafficLightsDirection {
	HORIZONTAL,	
	VERTICAL,	
	ALL
};


class Intersection : public Object
{
private:
	pair<ConnectInter, Vector2D> locationPair;
	Vector2D m_dimensions; 
	Vector2D carPos;	//used in stopCar function
	float carHeading;	//used in stopCar function
	Vector2D interPos;	//position of intersection


	float hLightTimer;	//horizontal timer
	float vLightTimer;	//vertical timer
	float hLightLimit;	//limits for timers
	float vLightLimit;
	bool m_highway;	//4 lane road?
	bool m_passed;	//vehicle passed the intersection?
	double m_passedTime;	//time spent on the intersection
	
	int directionAmount;	//amount of roads connected to the intersection
	vector<int> vLightsIDs;	//IDs of the vertical and horizontal lights
	vector<int> hLightsIDs;

	map<char, bool> directions;	//directions car can travel to from the intersection
	vector<pair<ConnectInter, Vector2D>> connectedLocations;	//connected locations
	vector<pair<bool, int>> connectedID;	//connected location ids
	unsigned int vehiclesPassed;	//amount vehicles passed by intersection
	
public:
	Intersection();
	Intersection(Vector2D dimensions, Vector2D position, float orientation, bool west, bool east, bool north, bool south, bool highway); 
	Vector2D getDimensions();
	LightStatus lStatus;	//traffic light status
	void lights(float timestep);	//function changing lights over (timestep) time
	void setLights(LightStatus lights);	//setting traffic light status
	LightStatus getLights();	//getting traffic light status
	void stopCar(Car &car1);	//function controlling cars at intersection
	void setConnectedLoc(ConnectInter direction, Vector2D position);	//hold data about directions and positions of connected intrsections
	void setConnectedID(bool building, int ID);	//holds data about connected location type and id
	vector<pair<bool, int>> getConnectedID();
	vector<pair<ConnectInter, Vector2D>> getConnectedLoc();

	map<char, bool> getDirections();	//holds data about amount of conencted objects
	void displayConnects();

	TrafficLightsDirection m_setTLights;	//set traffic lights
	TrafficLightsDirection greenLights;		//green lights?

	void setLightsTimer(TrafficLightsDirection setLights, float time);

	void setHLightTimer(float time);
	void setVLightTimer(float time);
	float getHorizontalTimer();
	float getVerticalTimer();

	void setHLightLimit(float time);
	void setVLightLimit(float time);
	float getHLimit();
	float getVLimit();
	
	void setVLightsIDs(int ID);
	void setHLightsIDs(int ID);

	void setColor();
	void setColor2();
	void setColorGreen();
	void setColorRed();
	
	vector<int> getVLightsIDs();
	vector<int> getHLightsIDs();

	void setPassed(bool passed);
	void setPassedTime(double time);
	bool getPassed();
	bool getType();
	int getDirectionAmount();
	double getPassedTime();
};

#endif