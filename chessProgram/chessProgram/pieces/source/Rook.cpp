/*
*  Definition of the Rook class.
*/

#include "Rook.h"

Rook::Rook(Color color)
{
    m_color = color;
    m_typeOfPiece = TypeOfPiece::PieceType::ROOK;
}

Rook::~Rook()
{
}

bool Rook::isValidMove(const Position& initPos, const Position& finalPos) const
{
    if (initPos == finalPos)
    { 
        return false;
    }
    // intersecting pieces are handled in the board manager class
    if (initPos.getX() == finalPos.getX() ||
        initPos.getY() == finalPos.getY())
    {
        return true;
    }
    return false;
}

std::vector<Position> Rook::getPath(const Position& initPos, const Position& finalPos) const 
{
    std::vector<Position> path;
    int pathLength = abs(initPos.getX() - finalPos.getX())
        + abs(initPos.getY() - finalPos.getY()) + 1;
    for (int i = 0; i < pathLength; i++)
    {
        if (initPos.getX() == finalPos.getX())
        {
            path.push_back(Position(initPos.getX(), std::min(initPos.getY(), finalPos.getY()) + i));
        }
        else
        {
            path.push_back(Position(std::min(initPos.getX(), finalPos.getX()) + i, initPos.getY()));
        }
    }
    return path;
}
