#include "stdafx.h"
#include "Object.h"


Object::Object() 
{

}

void Object::draw(sf::RenderTarget &target, sf::RenderStates states) const 
{
	target.draw(*m_renderShape);
}

void Object::update(float p_timestep)
{
	//updating objects position based on its heading
	float velX = sin((3.14159265359f / 180)*m_fOrientation) * m_speed * p_timestep;
	float velY = cos((3.14159265359f / 180)*m_fOrientation) * m_speed * p_timestep;

	m_velocity.set(velX, velY);

	m_position = m_position + m_velocity;


	// Move the object
	m_renderShape->setPosition(m_position.x(), m_position.y());
	m_renderShape->setRotation(-m_fOrientation);
}


Vector2D Object::getPosition()
{
	return m_position;
}

float Object::getSpeed()
{
	return m_speed;
}

float Object::getOrientation()
{
	return m_fOrientation;
}