/*
*	Definition of the Piece class.
*/

#include "Piece.h"

Color Piece::getColor() const
{
	return m_color;
}

void Piece::setColor(Color color)
{
	m_color = color;
}