#include "stdafx.h"
#include "HUD.h"

HUD::HUD()
{
	isPaused = true;
	report = false;
	currentButton = NONE;

	font.loadFromFile("XeroxSans.ttf");

	setText(paused, 24, 650, 10, "Paused: Press space to toggle pause.");
	setText(controls, 24, 10, 50, "When selected a building or an intersection,\nPress + or W to increase frequency value.\nPress - or S to decrease frequency value.\nClick and drag mouse to move camera.");
	setText(destinationB, 14, 32, 838, "Set Destination");
	setText(randomB, 14, 150, 838, "Random Dest");
	setText(spawnFreq, 24, 1280, 850, "Spawn Frequency: 5.00");
	setText(start, 24, 10, 10, "Pick start point");
	setText(end, 24, 10, 10, "Pick Destination");
	setText(lowestFrequency, 24, 1280, 825, "Lowest light duration: ");
	setText(highestFrequency, 24, 1280, 850, "Highest light duration: ");
	setText(lowestDuration, 24, 1280, 825, "Lowest spawn frequency: ");
	setText(highestDuration, 24, 1280, 850, "Highest spawn frequency: ");
	setText(horizontalInter, 24, 1280, 850, "Duration of horizontal lights: 10");
	setText(verticalInter, 24, 1280, 825, "Duration of vertical lights: 10");
	setText(verticalInterB, 14, 262, 838, "Vertical Freq");
	setText(horizontalInterB, 14, 142, 838, "Horizontal Freq");
	setText(allBuildingsB, 14, 32, 783, "All Buildings");
	setText(allIntersectionsB, 14, 32, 728, "All Junctions");
	setText(endSimB, 14, 702, 838, "End Simulation");

	setText(simDuration, 24, 32, 50, "Simulation Duration: ");
	setText(currentVehicles, 24, 32, 110, "Vehicles still on roads: ");
	setText(spawnedVehicles, 24, 32, 140, "Spawned vehicles: ");
	setText(arrivedVehicles, 24, 32, 170, "Arrived vehicles: ");
	setText(shortestArrival, 24, 32, 200, "Shortest driving time: ");
	setText(longestArrival, 24, 32, 230, "Longest driving time: ");
	setText(averageArrival, 24, 32, 260, "Average driving time: ");
	setText(leastUsedInter, 24, 32, 290, "Least used junction is highlighted green.");
	setText(mostUsedInter, 24, 32, 320, "Most used junction is highlighted red.");
	setText(exit, 24, 32, 410, "Press escape to exit simulation.");


	destination = HUDObj(Vector2D(100.f, 50.f), Vector2D(80.f, 850.f));
	interHorizontal = HUDObj(Vector2D(100.f, 50.f), Vector2D(190.f, 850.f));
	interVertical = HUDObj(Vector2D(100.f, 50.f), Vector2D(300.f, 850.f));
	randDestination = HUDObj(Vector2D(100.f, 50.f), Vector2D(190.f, 850.f));
	allBuildings = HUDObj(Vector2D(100.f, 50.f), Vector2D(80.f, 795.f));
	allIntersections = HUDObj(Vector2D(100.f, 50.f), Vector2D(80.f, 740.f));
	m_endSim = HUDObj(Vector2D(100.f, 50.f), Vector2D(750.f, 850.f));
	reportScreen = HUDObj(Vector2D(800.f, 900.f), Vector2D(400.f, 450.f));
	reportScreen.setColorWhite();
}

void HUD::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	if (!report)
	{
		if (isPaused)
		{
			target.draw(controls);
			target.draw(paused);
		}
		target.draw(destination);
		target.draw(destinationB);
		target.draw(allBuildings);
		target.draw(allIntersections);
		target.draw(allBuildingsB);
		target.draw(allIntersectionsB);
		target.draw(m_endSim);
		target.draw(endSimB);

		if (m_type == 1)
		{
			target.draw(interHorizontal);
			target.draw(interVertical);
			target.draw(horizontalInter);
			target.draw(verticalInter);
			target.draw(horizontalInterB);
			target.draw(verticalInterB);
		}
		if (m_type == 2)
		{
			target.draw(randDestination);
			target.draw(spawnFreq);
			target.draw(randomB);
		}
		if (m_type == 3)
		{
			target.draw(lowestDuration);
			target.draw(highestDuration);

		}
		if (m_type == 4)
		{
			target.draw(lowestFrequency);
			target.draw(highestFrequency);
		}
		switch (currentButton)
		{
		case PATH_START: target.draw(start); break;
		case PATH_END: target.draw(end); break;
		case NONE: break;
		default: break;
		}
	}
	else
	{
		target.draw(reportScreen);
		target.draw(simDuration);
		target.draw(currentVehicles);
		target.draw(spawnedVehicles);
		target.draw(arrivedVehicles);
		target.draw(shortestArrival);
		target.draw(longestArrival);
		target.draw(averageArrival);
		target.draw(leastUsedInter);
		target.draw(mostUsedInter);
		target.draw(exit);
		if (m_type == 1)
		{
			target.draw(horizontalInter);
			target.draw(verticalInter);
		}
		if (m_type == 2)
		{
		target.draw(spawnFreq);
		}
	}
}

ButtonClicked HUD::findMouseClick(float x, float y)
{
	int buildNo = -1;
	if (!report)
	{
		destination.setColor2();
		interVertical.setColor2();
		interHorizontal.setColor2();
		allBuildings.setColor2();
		allIntersections.setColor2();

		if (x < allBuildings.getPosition().x() + 50 && y < allBuildings.getPosition().y() + 25 && x > allBuildings.getPosition().x() - 50 && y > allBuildings.getPosition().y() - 25)
		{
			//buildNo = distance(buildings.begin(), it);
			allBuildings.setColor();
			m_type = 1;
			return ALL_BUILDS;
		}
		else if (x < allIntersections.getPosition().x() + 50 && y < allIntersections.getPosition().y() + 25 && x > allIntersections.getPosition().x() - 50 && y > allIntersections.getPosition().y() - 25)
		{
			//buildNo = distance(buildings.begin(), it);
			allIntersections.setColor();
			m_type = 2;
			return ALL_INTERS;
		}
		else if (x < destination.getPosition().x() + 50 && y < destination.getPosition().y() + 25 && x > destination.getPosition().x() - 50 && y > destination.getPosition().y() - 25)
		{
			//buildNo = distance(buildings.begin(), it);
			destination.setColor();
			randDestination.setColor2();
			return PATH;
		}
		else if (m_type == 1 && x < interHorizontal.getPosition().x() + 50 && y < interHorizontal.getPosition().y() + 25 && x > interHorizontal.getPosition().x() - 50 && y > interHorizontal.getPosition().y() - 25)
		{
			//buildNo = distance(buildings.begin(), it);
			interHorizontal.setColor();
			return INTERSECT_H;
		}
		else if (m_type == 1 && x < interVertical.getPosition().x() + 50 && y < interVertical.getPosition().y() + 25 && x > interVertical.getPosition().x() - 50 && y > interVertical.getPosition().y() - 25)
		{
			//buildNo = distance(buildings.begin(), it);
			interVertical.setColor();
			return INTERSECT_V;
		}
		else if (m_type == 2 && x < randDestination.getPosition().x() + 50 && y < randDestination.getPosition().y() + 25 && x > randDestination.getPosition().x() - 50 && y > randDestination.getPosition().y() - 25)
		{
			//buildNo = distance(buildings.begin(), it);
			randDestination.setColor();
			return RANDOM;
		}
	}

		return NOT_CLICKED;
}

void HUD::displaySpawnFreqency(float frequency)
{
	stringstream ss;
	ss << fixed << setprecision(2) << frequency;
	string s = ss.str();
	spawnFreq.setString("Spawn Frequency: " + s);
	m_type = 2;
}

void HUD::displayInterFrequency(float vFrequency, float hFrequency)
{
	stringstream ss;
	ss << fixed << setprecision(2) << vFrequency;
	string s = ss.str();
	verticalInter.setString("Duration of vertical lights: " + s);

	stringstream ss2;
	ss2 << fixed << setprecision(2) << hFrequency;
	s = ss2.str();
	horizontalInter.setString("Duration of horizontal lights: " + s);
	m_type = 1;
}

void HUD::allInterFrequency(pair<float,float> allFrequency)
{
	stringstream ss;
	ss << fixed << setprecision(2) << allFrequency.first;
	string s = ss.str();
	lowestFrequency.setString("Lowest light duration: " + s);

	stringstream ss2;
	ss2 << fixed << setprecision(2) << allFrequency.second;
	s = ss2.str();
	highestFrequency.setString("Highest light duration: " + s);
}

void HUD::allSpawnFrequency(pair<float, float> allFrequency)
{
	stringstream ss;
	ss << fixed << setprecision(2) << allFrequency.first;
	string s = ss.str();
	lowestDuration.setString("Lowest spawn frequency: "  + s);

	stringstream ss2;
	ss2 << fixed << setprecision(2) << allFrequency.second;
	s = ss2.str();
	highestDuration.setString("Highest spawn frequency: " + s);
}


void HUD::displayButtons(int type)
{
	m_type = type;
	//std::cout << m_type;
}

void HUD::reactToButton(ButtonPressed button)
{
	currentButton = button;

}

bool HUD::endSim(float x, float y)
{
	if (!report && x < m_endSim.getPosition().x() + 50 && y < m_endSim.getPosition().y() + 25 && x > m_endSim.getPosition().x() - 50 && y > m_endSim.getPosition().y() - 25)
	{
		randDestination.setColor();
		report = true;
		return report;
	}
	return report;
}

void HUD::setText(sf::Text &text, unsigned int size, float x, float y, sf::String caption)
{
	text.setFont(font);
	text.setCharacterSize(size);
	text.setColor(sf::Color::Black);
	text.setPosition(x, y);
	text.setString(caption);
}

void HUD::setUpReport(unsigned int current, unsigned int spawned, unsigned int arrived, double shortestTime, double longestTime, double summedTime, double duration)
{
	std::cout << spawned << " " << arrived << " " << shortestTime << " " << longestTime << " " << summedTime << std::endl;

	hours = 0;
	minutes = 0;
	seconds = 0;




	m_rVehAmount = current;

	std::stringstream ss;
	ss << m_rVehAmount;
	currentVehicles.setString("Vehicles still on roads : " + ss.str());

	m_rSpawned = spawned;
	ss.str(std::string());
	ss.clear();
	ss << m_rSpawned;
	spawnedVehicles.setString("Spawned vehicles: " + ss.str());

	m_rArrived = arrived;
	ss.str(std::string());
	ss.clear();
	ss << m_rArrived;
	arrivedVehicles.setString("Arrived vehicles: " + ss.str());


	m_rShortest = shortestTime;
	if (m_rShortest == 9999999)
	{
		m_rShortest = 0;
	}
	setTimeToDisplay(m_rShortest);
	shortestArrival.setString("Shortest arrival time: " + ssH.str() + ':' + ssM.str() + ':' + ssS.str());


	m_rLongest = longestTime;
	setTimeToDisplay(m_rLongest);
	longestArrival.setString("Longest arrival time: " + ssH.str() + ':' + ssM.str() + ':' + ssS.str());


	m_rSummed = summedTime;
	m_rAverage = m_rSummed / m_rArrived;
	if (m_rArrived == 0)
	{
		m_rAverage = 0;
	}
	setTimeToDisplay(m_rAverage);
	averageArrival.setString("Average arrival time: " + ssH.str() + ':' + ssM.str() + ':' + ssS.str());


	m_rDuration = duration;
	setTimeToDisplay(m_rDuration);
	simDuration.setString("Simulation duration: " + ssH.str() + ':' + ssM.str() + ':' + ssS.str());

}

void HUD::setPaused()
{
	if (isPaused == true)
		isPaused = false;
	else
		isPaused = true;
}

void HUD::setRandomButtonColour(bool isRandom)
{
	if (isRandom)
	{
		randDestination.setColor2();
	}
	else
	{
		randDestination.setColor();
	}
}

void HUD::setTimeToDisplay(double secs)
{
	seconds = (int)secs;
	minutes = seconds / 60;
	seconds = seconds % 60;
	hours = minutes / 60;
	minutes = minutes % 60;

	ssH.str(std::string());
	ssH.clear();
	ssM.str(std::string());
	ssM.clear();
	ssS.str(std::string());
	ssS.clear();

	ssH << hours;
	if (minutes < 10)
		ssM << setfill('0') << setw(2) << minutes;
	else
		ssM << minutes;

	if (seconds < 10)
		ssS << setfill('0') << setw(2) << seconds;
	else
		ssS << seconds;
}

