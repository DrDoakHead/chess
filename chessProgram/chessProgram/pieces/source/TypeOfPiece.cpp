/*
* Definition of TypeOfPiece class
*/

#include "TypeOfPiece.h"

TypeOfPiece::TypeOfPiece() :
	pieceType(UNKNOWN)
{
}

TypeOfPiece::~TypeOfPiece()
{
}

TypeOfPiece::TypeOfPiece(TypeOfPiece::PieceType type) :
	pieceType(type)
{
}

std::string TypeOfPiece::toString() const
{
	switch (pieceType)
	{
		case UNKNOWN:
			return "UNKNOWN";
		case KING:
			return "KING";
		case ROOK:
			return "ROOK";
		case QUEEN:
			return "QUEEN";
		case BISHOP:
			return "BISHOP";
		case PAWN:
			return "PAWN";
	}
}

std::string TypeOfPiece::toString(PieceType type)
{
	switch (type)
	{
	case UNKNOWN:
		return "UNKNOWN";
	case KING:
		return "KING";
	case ROOK:
		return "ROOK";
	case QUEEN:
		return "QUEEN";
	case BISHOP:
		return "BISHOP";
	case PAWN:
		return "PAWN";
	}
}

TypeOfPiece::PieceType TypeOfPiece::fromString(const std::string& value)
{
	if (value == "KING")
	{
		return KING;
	}
	else if (value == "ROOK")
	{
		return ROOK;
	}
	else if (value == "QUEEN")
	{
		return QUEEN;
	}
	else if (value == "BISHOP")
	{
		return BISHOP;
	}
	else if (value == "PAWN")
	{
		return PAWN;
	}
	else
	{
		return UNKNOWN;
	}
}