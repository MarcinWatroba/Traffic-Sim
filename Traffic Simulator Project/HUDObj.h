#ifndef HUDOBJ_H
#define HUDOBJ_H

#include "Vector2D.h"
#include <iostream>
#include <SFML/Graphics.hpp>

class HUDObj : public sf::Drawable
{
protected:
	sf::Shape * m_renderShape;
	Vector2D m_position;
	Vector2D m_dimensions;
public:
	HUDObj();
	HUDObj(Vector2D dimensions, Vector2D position);
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	void setColor();
	void setColorWhite();
	void setColor2();


	Vector2D getPosition();
};

#endif