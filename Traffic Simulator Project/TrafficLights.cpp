#include "stdafx.h"
#include "TrafficLights.h"

TrafficLights::TrafficLights()
{
	m_dimensions.set(0.f, 0.0f);
	m_position.set(0.0f, 0.0f);
	m_fOrientation = 0.0f;
	lColour = RED_COLOUR;

	sf::RectangleShape * tLights = new sf::RectangleShape();
	tLights->setSize(sf::Vector2f(m_dimensions.x(), m_dimensions.y()));
	tLights->setOrigin(m_dimensions.x() / 2.0f, m_dimensions.y() / 2.0f);
	tLights->setPosition(m_position.x(), m_position.y());
	tLights->setRotation(-m_fOrientation);
	tLights->setFillColor(sf::Color::Red);
	m_renderShape = tLights;
}

TrafficLights::TrafficLights(Vector2D dimensions, Vector2D position, float orientation, LightColour colour)
{
	m_dimensions = dimensions;
	m_position = position;
	m_fOrientation = orientation;
	lColour = colour;

	sf::RectangleShape * tLights = new sf::RectangleShape();
	tLights->setSize(sf::Vector2f(m_dimensions.x(), m_dimensions.y()));
	tLights->setOrigin(m_dimensions.x() / 2.0f, m_dimensions.y() / 2.0f);
	tLights->setPosition(m_position.x(), m_position.y());
	tLights->setRotation(-m_fOrientation);
	tLights->setFillColor(sf::Color::Red);
	if (lColour == GREEN_COLOUR)
	{
		tLights->setFillColor(sf::Color::Green);
	}
	else if (lColour == RED_COLOUR)
	{
		tLights->setFillColor(sf::Color::Red);
	}
	else
	{
		tLights->setFillColor(sf::Color::Yellow);
	}
	m_renderShape = tLights;
}

Vector2D TrafficLights::getDimensions()
{
	return m_dimensions;
}

void TrafficLights::changeColour()
{

}

void TrafficLights::setLights()
{

	//set light colour

	if (lColour == GREEN_COLOUR)
	{	
		m_renderShape->setFillColor(sf::Color::Yellow);
		lColour = YELLOW_COLOUR;
	}
	else if (lColour == YELLOW_COLOUR)
	{
		m_renderShape->setFillColor(sf::Color::Red);
		lColour = RED_COLOUR;
	}
	else
	{
		m_renderShape->setFillColor(sf::Color::Green);
		lColour = GREEN_COLOUR;
	}
}

