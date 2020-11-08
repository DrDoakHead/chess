/*
*	Definition of the Position class.
*/

#include "Position.h"
#include <stdexcept>
#include <stdio.h>

/*
* Default constructor.  Initalize position to invalid (0, 0)
*/
Position::Position()
{
	// TODO: Autogen constructor
}

Position::Position(const uint8_t x, const uint8_t y)
{
	if (isNumberValid(x) && isNumberValid(y))
	{
		m_x = x;
		m_y = y;
	}
}

int8_t Position::getX() const
{
	return m_x;
}

void Position::setX(int8_t x)
{
	if (isNumberValid(x))
	{
		m_x = x;
	}
}

int8_t Position::getY() const
{
	return m_y;
}

void Position::setY(int8_t y)
{
	if (isNumberValid(y))
	{
		m_y = y;
	}
}

Position Position::operator=(const Position& rhs)
{
	if (this != &rhs)
	{
		m_x = rhs.m_x;
		m_y = rhs.m_y;
	}
	return *this;
}

bool Position::operator==(const Position& rhs)
{
	if (m_x != rhs.m_x || m_y != rhs.m_y)
	{
		return false;
	}
	return true;
}

bool Position::operator!=(const Position& rhs)
{
	if (this == &rhs)
	{
		return false;
	}
	return true;
}

Position Position::operator+(const Position& rhs)
{
	if (isNumberValid(m_x + rhs.m_x) && (isNumberValid(m_y + rhs.m_y)))
	{
		m_x += rhs.m_x;
		m_y += rhs.m_y;
		return *this;
	}
	else
	{
		return Position();
	}
}

Position Position::operator-(const Position& rhs)
{
	if (isNumberValid(m_x - rhs.m_x) && (isNumberValid(m_y - rhs.m_y)))
	{
		m_x -= rhs.m_x;
		m_y -= rhs.m_y;
		return *this;
	}
	else
	{
		return Position();
	}
}

bool Position::isNumberValid(const int8_t numToCheck)
{
	if (numToCheck > 0 && numToCheck < 9)
	{
		return true;
	}
	else
	{
		//std::cout << "invalid number given" << std::endl;
		return false;
	}
}

