//main.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include "Scene.h"
#include "HUD.h"
#include <string>
#include <iomanip>
#include <sstream>

int main()
{
	srand(time(NULL));
	Scene scene;
	HUD display;

	sf::RenderWindow window(sf::VideoMode(1100, 600), "Traffic Simulator");

	sf::Clock clock; // Game time clock
	sf::Clock drawClock;
	sf::Clock spawnClock; // spawn timer
	float savedClock = 0.f;
	float savedSpawnClock = 0.f;

	float lastTime = 0;
	float time = 5;
	float x = 0;
	float y = 0;
	float lastX = 0;
	float lastY = 0;
	float dX = 0;
	float dY = 0;
	bool paused = true;
	bool report = false;
	bool gotData = false;

	pair<float, float> spawnLimits;
	pair<float, float> lightLimits;
	pair<float, float> limits;
	pair<ObjectType, int> object = make_pair(BUILDING, 0);
	pair<ObjectType, int>  lObject = make_pair(BUILDING, 0);
	pair<ObjectType, int>  buildingo = make_pair(NOTHING, -1);
	pair<ObjectType, int>  buildingos = make_pair(NOTHING, -1);
	int etap = 0;
	ButtonClicked clicked = NOT_CLICKED;

	//text.setString("Spawn Frequency: 5.00");
	sf::View main(sf::Vector2f(800, 450), sf::Vector2f(1600, 900));
	sf::View hud(sf::Vector2f(800, 450), sf::Vector2f(1600, 900));

	// run the program as long as the window is open
	while (window.isOpen())
	{

		window.clear();
		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		while (window.pollEvent(event))
		{
			// "close requested" event: close the window
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed && !report)
			{
				switch (event.key.code)
				{
				case sf::Keyboard::Add:  

										 if (clicked == ALL_BUILDS) limits = scene.setAllBuildingSpawn(+0.5);
										 else if (clicked == ALL_INTERS) limits = scene.setAllLightsTime(+0.5);
										 else if (object.first == BUILDING) scene.setBuildingSpawn(object.second, +0.5);
										 else if (object.first == INTERSECT  && clicked == INTERSECT_V) scene.setLightsTime(VERTICAL, object.second, +0.5);
										 else if (object.first == INTERSECT  && clicked == INTERSECT_H) scene.setLightsTime(HORIZONTAL, object.second, +0.5);
										 else if (object.first == INTERSECT)  scene.setLightsTime(ALL, object.second, +0.5);
										 break;
				case sf::Keyboard::Subtract: 
											if (clicked == ALL_BUILDS) limits = scene.setAllBuildingSpawn(-0.5);
											else if (clicked == ALL_INTERS) limits = scene.setAllLightsTime(-0.5);
											else if (scene.getBuildingSpawn(object.second)>0.5f && object.first == BUILDING) scene.setBuildingSpawn(object.second, -0.5);
											else if (object.first == INTERSECT && clicked == INTERSECT_V && scene.getLightsV(object.second) > 3.0f) scene.setLightsTime(VERTICAL, object.second, -0.5);
											else if (object.first == INTERSECT && clicked == INTERSECT_H && scene.getLightsH(object.second) > 3.0f) scene.setLightsTime(HORIZONTAL, object.second, -0.5);
											else if (object.first == INTERSECT && scene.getLightsH(object.second) > 3.0f && scene.getLightsV(object.second) > 3.0f)  scene.setLightsTime(ALL, object.second, -0.5);
											break;
				case sf::Keyboard::W:

											if (clicked == ALL_BUILDS) limits = scene.setAllBuildingSpawn(+0.5);
											else if (clicked == ALL_INTERS) limits = scene.setAllLightsTime(+0.5);
											else if (object.first == BUILDING) scene.setBuildingSpawn(object.second, +0.5);
											else if (object.first == INTERSECT  && clicked == INTERSECT_V) scene.setLightsTime(VERTICAL, object.second, +0.5);
											else if (object.first == INTERSECT  && clicked == INTERSECT_H) scene.setLightsTime(HORIZONTAL, object.second, +0.5);
											else if (object.first == INTERSECT)  scene.setLightsTime(ALL, object.second, +0.5);
											break;
				case sf::Keyboard::S:
											if (clicked == ALL_BUILDS) limits = scene.setAllBuildingSpawn(-0.5);
											else if (clicked == ALL_INTERS) limits = scene.setAllLightsTime(-0.5);
											else if (scene.getBuildingSpawn(object.second)>0.5f && object.first == BUILDING) scene.setBuildingSpawn(object.second, -0.5);
											else if (object.first == INTERSECT && clicked == INTERSECT_V && scene.getLightsV(object.second) > 3.0f) scene.setLightsTime(VERTICAL, object.second, -0.5);
											else if (object.first == INTERSECT && clicked == INTERSECT_H && scene.getLightsH(object.second) > 3.0f) scene.setLightsTime(HORIZONTAL, object.second, -0.5);
											else if (object.first == INTERSECT && scene.getLightsH(object.second) > 3.0f && scene.getLightsV(object.second) > 3.0f)  scene.setLightsTime(ALL, object.second, -0.5);
											break;

				case sf::Keyboard::Space: 
											if (!paused) 
											{ 
												savedClock = clock.getElapsedTime().asSeconds(); 
												savedSpawnClock = spawnClock.getElapsedTime().asSeconds();
												paused = true;
											}
											else
											{
												clock.restart();
												spawnClock.restart();
												paused = false;
											}
											display.setPaused();
											break;
				case sf::Keyboard::Escape:
					window.close();

				default: break;
				}

				if (object.first == BUILDING)
				{
					display.displaySpawnFreqency(scene.getBuildingSpawn(object.second));
				}
				if (object.first == INTERSECT)
				{
					display.displayButtons(1);
					display.displayInterFrequency(scene.getLightsV(object.second), scene.getLightsH(object.second));
				}
				if (clicked == ALL_INTERS)
				{
					display.allInterFrequency(limits);
					display.displayButtons(4);

				}
				if (clicked == ALL_BUILDS)
				{
					display.allSpawnFrequency(limits);
					display.displayButtons(3);

				}

			}
			else if (event.type == sf::Event::KeyPressed && report)
			{
				switch (event.key.code)
				{
				case sf::Keyboard::Escape:
					window.close();

				default: break;
				}
			}
			x = sf::Mouse::getPosition(window).x;
			y = sf::Mouse::getPosition(window).y; 
			dX = lastX - x;
			dY = lastY - y;
			lastX = x;
			lastY = y;

			if (event.type == sf::Event::MouseButtonPressed)
			{

				sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
				sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos,main);
				sf::Vector2f hudPos = window.mapPixelToCoords(pixelPos, hud);

				if (!report)
				{

					if (clicked == PATH)
					{

						if (etap == 0)
						{

							buildingo = scene.findMouseClick(worldPos.x, worldPos.y, true);

							if (buildingo.first == BUILDING)
							{
								etap = 1;
								display.reactToButton(PATH_END);
							}
						}
						else  if (etap == 1)
						{

							buildingos = scene.findMouseClick(worldPos.x, worldPos.y, false);
							std::cout << buildingos.first << std::endl;
							if (buildingos.first == BUILDING)
							{
								std::cout << buildingos.first << std::endl;
								etap = 2;
								display.reactToButton(NONE);
							}
						}
						if (etap == 2)
						{
							object = scene.findMouseClick(worldPos.x, worldPos.y, true);

							scene.setBuildingGoal(buildingo.second, false, buildingos.second);
							buildingo = make_pair(NOTHING, -1);
							buildingos = make_pair(NOTHING, -1);
							etap = 0;
							clicked = display.findMouseClick(hudPos.x, hudPos.y);
						}
					}
					else
					{
						report = display.endSim(hudPos.x, hudPos.y);
						clicked = display.findMouseClick(hudPos.x, hudPos.y);
						display.displayButtons(0);
						if (clicked == PATH)
						{
							display.reactToButton(PATH_START);
						}
						else if (clicked == ALL_BUILDS)
						{

							limits = scene.setAllBuildingSpawn(0);

						}
						else if (clicked == ALL_INTERS)
						{

							limits = scene.setAllLightsTime(0);

						}
						if (clicked == NOT_CLICKED || PATH)
						{
							object = scene.findMouseClick(worldPos.x, worldPos.y, true);
						}
						if (object.second == -1)
						{
							object = lObject;
						}
						if (object.first == INTERSECT)
						{
							display.displayButtons(1);
							display.displayInterFrequency(scene.getLightsV(object.second), scene.getLightsH(object.second));
						}

						lObject = object;
						if (object.first == BUILDING)
						{
							display.displaySpawnFreqency(scene.getBuildingSpawn(object.second));
							display.displayButtons(2);
							display.setRandomButtonColour(scene.getIsBuildingRandom(object.second));

						}
						if (clicked == RANDOM && object.first == BUILDING)
						{
							scene.setBuildingGoal(object.second, true, object.second);
							display.setRandomButtonColour(scene.getIsBuildingRandom(object.second));
						}
						if (clicked == ALL_INTERS)
						{
							display.allInterFrequency(limits);
							display.displayButtons(4);
						}
						if (clicked == ALL_BUILDS)
						{
							display.allSpawnFrequency(limits);
							display.displayButtons(3);
						}
					}




				}
				else
				{
					object = scene.findMouseClickReport(worldPos.x, worldPos.y, true);

					if (object.first == INTERSECT)
					{
						display.displayInterFrequency(scene.getLightsV(object.second), scene.getLightsH(object.second));
					}
					lObject = object;
					if (object.first == BUILDING)
					{
						display.displaySpawnFreqency(scene.getBuildingSpawn(object.second));

					}

				}


	
			}
			
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{

					main.move(dX, dY);


			}

		}

		
		
		//call spawn function every 3.5 seconds, send elapsed time as parameter (currently not used)
		if (!paused && !report)
		{
			if (spawnClock.getElapsedTime().asSeconds() > 0.5 - savedSpawnClock)
			{
				scene.spawn(spawnClock.getElapsedTime().asSeconds());
				scene.changeLights(spawnClock.getElapsedTime().asSeconds());
				savedSpawnClock = 0.f;
				spawnClock.restart();
			}

			//call update function every 0.005 seconds
			if (clock.getElapsedTime().asSeconds() > 0.01 - savedClock)
			{
				scene.update(clock.getElapsedTime().asSeconds());
				clock.restart();
				savedSpawnClock = 0.f;
			}

		}
		if (drawClock.getElapsedTime().asSeconds() > 0.01)
		{
			window.clear(sf::Color::White);
			window.setView(main);
			window.draw(scene);
			window.setView(hud);
			window.draw(display);
			window.display();
			drawClock.restart();
		}
		if (report && !gotData)
		{
			unsigned int carAmount = scene.getVehSize();
			unsigned int spawned = scene.getSpawnedAmount();
			unsigned int arrived = scene.getArrivedAmount();
			double shortest = scene.getShortestTimeDriving();
			double longest = scene.getLongestTimeDriving();
			double summed = scene.getSummedTimeDriving();
			double simDur = scene.getSimulationDuration();
			scene.getIntersectionPasses();
			display.setUpReport(carAmount, spawned, arrived, shortest, longest, summed, simDur);
			gotData = true;
		}
	}

    return 0;
}

