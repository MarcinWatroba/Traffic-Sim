#ifndef HUD_H
#define HUD_H

#include <SFML/Graphics.hpp>
#include <string>
#include <iomanip>
#include <sstream>
#include "HUDObj.h"

enum ButtonPressed {
	NONE,
	PATH_START,
	PATH_END

};

enum ButtonClicked {
	PATH,
	RANDOM,
	INTERSECT_H,
	INTERSECT_V,
	NOT_CLICKED,
	ALL_BUILDS,
	ALL_INTERS
};

class HUD : public sf::Drawable
{
private:
	sf::Font font;

	HUDObj destination;
	sf::Text destinationB;
	HUDObj randDestination;
	sf::Text randomB;
	HUDObj interHorizontal;
	sf::Text horizontalInterB;
	HUDObj interVertical;
	sf::Text verticalInterB;
	HUDObj allBuildings;
	sf::Text allBuildingsB;
	HUDObj allIntersections;
	sf::Text allIntersectionsB;

	HUDObj m_endSim;
	sf::Text endSimB;

	HUDObj reportScreen;

	sf::Text paused;
	sf::Text controls;
	sf::Text spawnFreq;
	sf::Text start;
	sf::Text end;
	sf::Text verticalInter;
	sf::Text horizontalInter;
	sf::Text highestDuration;
	sf::Text lowestDuration;
	sf::Text highestFrequency;
	sf::Text lowestFrequency;

	sf::Text currentVehicles;
	sf::Text spawnedVehicles;
	sf::Text arrivedVehicles;
	sf::Text shortestArrival;
	sf::Text longestArrival;
	sf::Text averageArrival;
	sf::Text simDuration;

	sf::Text leastUsedInter;
	sf::Text mostUsedInter;
	sf::Text exit;

	int m_type;

	bool report;

	unsigned int m_rVehAmount;
	unsigned int m_rSpawned;
	unsigned int m_rArrived;
	double m_rShortest;
	double m_rLongest;
	double m_rSummed;
	double m_rAverage;
	double m_rDuration;
	int hours;
	int minutes;
	int seconds;
	bool isPaused;

	std::stringstream ssH;
	std::stringstream ssM;
	std::stringstream ssS;

public:
	HUD();
	void draw(sf::RenderTarget &target, sf::RenderStates states) const; //drawing all objects in the scene
	ButtonClicked findMouseClick(float x, float y);
	void displaySpawnFreqency(float frequency);
	void displayInterFrequency(float vFrequency, float hFrequency);
	void allInterFrequency(pair<float, float> allFrequency);
	void allSpawnFrequency(pair<float, float> allFrequency);
	ButtonPressed currentButton;
	ButtonClicked buttonClicked;
	void displayButtons(int type);
	void reactToButton(ButtonPressed button);
	bool endSim(float x, float y);
	void setText(sf::Text &text, unsigned int size, float x, float y, sf::String caption);
	void setUpReport(unsigned int current, unsigned int spawned, unsigned int arrived, double shortestTime, double longestTime, double summedTime, double duration);
	void  setPaused();
	void setRandomButtonColour(bool isRandom);
	void setTimeToDisplay(double secs);
};

#endif