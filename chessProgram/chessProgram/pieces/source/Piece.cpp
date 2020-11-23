/*
*	Definition of the Piece class.
*/

#include "Piece.h"

Piece::Piece() :
	m_color(Color::UNKNOWN),
	m_typeOfPiece(TypeOfPiece::PieceType::UNKNOWN)
{
}

Piece::Piece(Color color, TypeOfPiece::PieceType pieceType) :
	m_color(color),
	m_typeOfPiece(pieceType)
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

std::string Piece::toString() const
{
	switch (m_typeOfPiece)
	{
	case TypeOfPiece::PAWN:
		return "Pawn";
	case TypeOfPiece::ROOK:
		return "Rook";
	case TypeOfPiece::BISHOP:
		return "Bishop";
	case TypeOfPiece::KNIGHT:
		return "Knight";
	case TypeOfPiece::QUEEN:
		return "Queen";
	case TypeOfPiece::KING:
		return "King";
	case TypeOfPiece::UNKNOWN:
	default:
		return "Unknown";
	}
	return "UNKNOWN";
}

TypeOfPiece::PieceType Piece::getType() const
{
	return m_typeOfPiece;
}