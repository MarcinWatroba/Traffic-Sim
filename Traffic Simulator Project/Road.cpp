#include "stdafx.h"
#include "Road.h"

Road::Road()
{
	m_dimensions.set(0.f, 0.0f);
	m_position.set(0.0f, 0.0f);
	m_fOrientation = 0.0f;

	sf::RectangleShape * road = new sf::RectangleShape();
	road->setSize(sf::Vector2f(m_dimensions.x(), m_dimensions.y()));
	road->setOrigin(m_dimensions.x() / 2.0f, m_dimensions.y() / 2.0f);
	road->setPosition(m_position.x(), m_position.y());
	road->setRotation(-m_fOrientation);
	road->setFillColor(sf::Color::Blue);
	m_renderShape = road;
}

Road::Road(Vector2D dimensions, Vector2D position, float orientation)
{
	m_dimensions = dimensions;
	m_position = position;
	m_fOrientation = orientation;

	sf::RectangleShape * road = new sf::RectangleShape();
	road->setSize(sf::Vector2f(m_dimensions.x(), m_dimensions.y()));
	road->setOrigin(m_dimensions.x() / 2.0f, m_dimensions.y() / 2.0f);
	road->setPosition(m_position.x(), m_position.y());
	road->setRotation(-m_fOrientation);
	road->setFillColor(sf::Color::Blue);
	m_renderShape = road;
}

Vector2D Road::getDimensions()
{
	return m_dimensions;
}