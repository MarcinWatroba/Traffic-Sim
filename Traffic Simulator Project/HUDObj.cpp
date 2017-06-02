#include "stdafx.h"
#include "HUDObj.h"

HUDObj::HUDObj()
{
	m_dimensions.set(0.f, 0.0f);
	m_position.set(0.0f, 0.0f);

	sf::RectangleShape * hudObj = new sf::RectangleShape();
	hudObj->setSize(sf::Vector2f(m_dimensions.x(), m_dimensions.y()));
	hudObj->setOrigin(m_dimensions.x() / 2.0f, m_dimensions.y() / 2.0f);
	hudObj->setPosition(m_position.x(), m_position.y());
	hudObj->setFillColor(sf::Color::Green);
	hudObj->setOutlineColor(sf::Color::Black);
	hudObj->setOutlineThickness(2.f);
	m_renderShape = hudObj;

}

HUDObj::HUDObj(Vector2D dimensions, Vector2D position)
{
	m_dimensions = dimensions;
	m_position = position;

	sf::RectangleShape * hudObj = new sf::RectangleShape();
	hudObj->setSize(sf::Vector2f(m_dimensions.x(), m_dimensions.y()));
	hudObj->setOrigin(m_dimensions.x() / 2.0f, m_dimensions.y() / 2.0f);
	hudObj->setPosition(m_position.x(), m_position.y());
	hudObj->setFillColor(sf::Color::Green);
	hudObj->setOutlineColor(sf::Color::Black);
	hudObj->setOutlineThickness(2.f);
	m_renderShape = hudObj;

}

void HUDObj::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(*m_renderShape);
}

Vector2D HUDObj::getPosition()
{
	return m_position;
}

void HUDObj::setColor()
{
	m_renderShape->setFillColor(sf::Color::Red);
}

void HUDObj::setColorWhite()
{
	m_renderShape->setFillColor(sf::Color::White);
}

void HUDObj::setColor2()
{
	m_renderShape->setFillColor(sf::Color::Green);
}