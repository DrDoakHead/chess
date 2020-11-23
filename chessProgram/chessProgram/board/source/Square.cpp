/*
  Implementation of the Square class
*/

#include "Square.h"

Square::Square() :
    m_position(),
    m_piece()
{
}

Square::~Square()
{
}

Square::Square(const Position& position, const std::shared_ptr<Piece>& piece) :
    m_position(position),
    m_piece(piece)
{
}

Position Square::getPosition() const 
{
    return m_position;
}

std::shared_ptr<Piece> Square::getPiece() const
{
    return m_piece;
}

bool Square::operator==(const Square& rhs) const
{
    if (rhs.getPosition() == m_position)
    {
        return true;
    }
    return false;
}

bool Square::operator!=(const Square& rhs) const
{
    if (this == &rhs)
    {
        return false;
    }
    return true;
}

bool Square::isOccupied() const 
{
    if (m_piece == nullptr) {
        return false;
    }
    return true;
}

std::string Square::getPieceString() const 
{
    if (m_piece == nullptr) {
        return "";
    }
    return m_piece->toString();
}

std::string Square::getPositionString() const
{
    return m_position.toString();
}

void Square::releasePiece() 
{
    m_piece = nullptr;
}

void Square::setPiece(const std::shared_ptr<Piece>& piece) 
{
    m_piece = piece;
}
