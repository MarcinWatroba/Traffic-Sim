#ifndef CAR_H
#define CAR_H

#include "Object.h"
#include "Building.h"

// car status used by cars to specify what they are currently doing
enum CarStatus {
	MOVING,
	ACCELERATING,
	DECELERATING,
	SLOWING_DOWN,
	LIGHTS_WAITING,
	QUEUE_WAITING,
	TRAFFIC_DETECTED,
};
// car location, specifying location of the cars
enum CarLocation {

	INTERSECTION,
	ROAD
};

// enum telling the car where it should turn on the next intersection, (towards connected intersection at north/west/east/south)
enum ConnectInter {
	NORTH,	
	WEST,	
	EAST,
	SOUTH
};

class Car : public Object
{
private:
	Vector2D m_dimensions;	//dimensioins
	Vector2D car2Pos;	//used in react function
	Vector2D goalLoc;	//location of the destination building
	//std::vector<Vector2D> detected;
	ConnectInter goal;	//turn the vehicle has to make at the current intersection
	ConnectInter nextGoal;	//turn the vehicle has to make at the next intersection
	Vector2D lowerBoundary;	//lower boundary of vehicle at its lane
	Vector2D higherBoundary;	//higher boundary of vehicle at its lane
	Vector2D  lowerBoundaryInter;	//lower boundary of vehicle at its lane and lane to the left
	Vector2D  higherBoundaryInter;	//higher boundary of vehicle at its lane and lane to the left
	ConnectInter car2goal;	//specifies current intersection turn of the other vehicle
	float car2heading;	//heading of the other vehicle
	float goalDist;	//distance to destination location
	int carBox;	//id of the collision grid that the car is currently in
	bool directionChosen;	//did vehicle already choose a direction of turn for current intersection?
	bool atIntersection;	//is the vehicle in the middle of intersection?
	bool horizontalWaiting;	//are 
	bool wait;	//is car giving way to other vehicle?
	bool blockingFlow;	//is car blocking flow at the intersection by waiting at the position through which other vehicles pass?
	//bool first;	
	float distToInter;	//distance to current intersection
	int turnNum;	//current iteration of the path vector
	vector<ConnectInter> path;	//ordered path vector of all necessary turns needed to be taken to reach destination
	bool onHighwayUp;	//is vehicle going up the highway? (north)
	bool onHighwayDown;	//is vehicle going down the highway? (south)
	Vector2D lastInter;	//last passed intersection
	bool changedLine;	//did vehicle already change lane at 4 lane road?
	double timeDriving;	
	float blockingTime;	//length of time the vehicle was blocking an intersection
protected:

public:
	Car();
	Car(Vector2D dimensions, Vector2D position, float speed, float orientation);

	void react(Car &car2);	//function modelling car behaviour against other traffic
	void turn(vector<pair<ConnectInter, Vector2D>> interPos, Vector2D interPos2, float distance, bool highway);	//function implementing turning at intersection
	
	CarStatus status;	//car status (moving, stopping, decelerating, detecting etc.)
	CarLocation loc;	//car location (intersection, road)

	//getter methods
	Vector2D getGoalLoc();
	ConnectInter getGoal();
	Vector2D getDimensions();
	double getTimeDriving();
	int getCarBox();
	bool getDirectionChosen();
	bool getAtIntersection();
	bool getBlocking();
	bool getWait();
	bool checkGoal();	//checking if car reached destination

	//setter methods
	void setSpeed(float speed);
	void setGoalPos(Vector2D pos);
	void setAtIntersection(bool inter);
	void setBlockingFlow(bool blocking);
	void setHorizontalWaiting(bool hWaiting);
	void setPath(vector<ConnectInter> paths);
	void setTimeDriving(double time);
	void setInterDist(float dist);
	void setCarbox(int box);
	void setGoal();
	void setDirectionChosen(bool chosen);
	void setBlockingTime(float time);
	void setColorOne();
	void setColorTwo();

};

#endif
