/*
*	Definition of the Position class.
*/

#include "Position.h"

Position::Position() :
	m_x(0),
	m_y(0)
{
}

Position::Position(const int8_t x, const int8_t y)
{
	if (isNumberValid(x) && isNumberValid(y))
	{
		m_x = x;
		m_y = y;
	}
}

Position::~Position()
{
}

int8_t Position::getX() const
{
	return m_x;
}

void Position::setX(const int8_t x)
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

void Position::setY(const int8_t y)
{
	if (isNumberValid(y))
	{
		m_y = y;
	}
}

std::string Position::toString() const
{
	std::string output;
	output = "x = " + m_x;
	output += ", y = " + m_y;
	return output;
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

bool Position::operator==(const Position& rhs) const
{
	if (m_x != rhs.m_x || m_y != rhs.m_y)
	{
		return false;
	}
	return true;
}

bool Position::operator!=(const Position& rhs) const
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

bool Position::isNumberValid(const int8_t numToCheck) const
{
	if (numToCheck > 0 && numToCheck < 9)
	{
		return true;
	}
	else
	{
		return false;
	}
}

