/*
*	Definition of the Piece class.
*/

#include "Piece.h"

Piece::Piece() :
	m_color(Color::UNKNOWN)
{
}

Piece::Piece(Color color) :
	m_color(color)
{
}

Piece::~Piece()
{
}

Color Piece::getColor() const
{
	return m_color;
}

void Piece::setColor(Color color)
{
	m_color = color;
}

TypeOfPiece::PieceType Piece::getType() const
{
	return TypeOfPiece::PieceType::UNKNOWN;
}