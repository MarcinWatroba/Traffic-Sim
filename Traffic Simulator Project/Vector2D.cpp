/**
@file vector2D.cpp
*/
#include "stdafx.h"
#include "Vector2D.h"


Vector2D::Vector2D()  // Default consturct, set everything to zero
{
	m_data[0] = 0;
	m_data[1] = 0;
}

Vector2D::Vector2D(float allValues) // Construtor taking a single value and making all component equal to that value
{
	m_data[0] = allValues;
	m_data[1] = allValues;
}


Vector2D::Vector2D(float x, float y) // Constructor taking x,y, and z values
{
	m_data[0] = x;
	m_data[1] = y;
}


float Vector2D::angle(Vector2D& other) const // angle between this vector and other
{
	return acos(dotProduct(other) / (magnitude() * other.magnitude()));
}


Vector2D Vector2D::unitVector()  const // Returns the unit vector of this vector
{
	float mag = magnitude();
	return Vector2D(m_data[0] / mag, m_data[1] / mag);
}


float Vector2D::x() const // Returns the X component of this vector 
{
	return m_data[0];
}


float Vector2D::y() const // Returns the Y component of this vector
{
	return m_data[1];
}

float Vector2D::magnitude() const// Returns the magnitude of this vector
{
	return sqrt(m_data[0] * m_data[0] + m_data[1] * m_data[1]);
}

Vector2D Vector2D::operator- (const Vector2D& other)  const// Component wise subtraction
{
	return Vector2D(m_data[0] - other.m_data[0], m_data[1] - other.m_data[1]);
}


Vector2D Vector2D::operator+ (const Vector2D& other)  const // Component wise addition
{
	return Vector2D(m_data[0] + other.m_data[0], m_data[1] + other.m_data[1]);
}


Vector2D Vector2D::operator* (const Vector2D& other)  const // Component wise multiplication
{
	return Vector2D(m_data[0] * other.m_data[0], m_data[1] * other.m_data[1]);
}


Vector2D Vector2D::operator* (const float scalar)  const // Component wise scalar multiplication
{
	return Vector2D(m_data[0] * scalar, m_data[1] * scalar);
}


float Vector2D::dotProduct(Vector2D& other)  const // Returns the dot product of this vector with other
{
	return m_data[0] * other.m_data[0] + m_data[1] * other.m_data[1];
}


float Vector2D::crossProduct(Vector2D& other)  const // Returns the cross product of this vector with other
{
	return (m_data[0] * other.m_data[1] - m_data[1] * other.m_data[0]);
}


Vector2D Vector2D::crossProduct(float scalar)  const
{
	Vector2D result(scalar * m_data[1], -scalar * m_data[0]);
	return result;
}

void Vector2D::set(float x, float y) // Set new values in the vector
{
	m_data[0] = x;
	m_data[1] = y;
}

float Vector2D::distance(Vector2D& other) const	//returns the distance of two objects
{	
	return sqrt(pow(other.m_data[0] - m_data[0], 2) + pow(other.m_data[1] - m_data[1], 2));
}