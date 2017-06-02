#ifndef OBJECT_H
#define OBJECT_H

#include "Vector2D.h"
#include <iostream>

class Object : public sf::Drawable
{
protected:
	//const double pi = 3.1415926535897;
	sf::Shape * m_renderShape; 
	Vector2D m_position;
	Vector2D m_velocity;
	float m_speed;
	float m_fOrientation;
	float distance;
public:
	Object();
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	void update(float timestep);
	Vector2D getPosition();
	float getSpeed();
	float getOrientation();
};

#endif