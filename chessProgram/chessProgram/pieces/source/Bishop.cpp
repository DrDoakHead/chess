/**
 * Implementation of the Bishop class
 */

#include "Bishop.h"

Bishop::Bishop(Color color)
{
    m_color = color;
    m_typeOfPiece = TypeOfPiece::PieceType::BISHOP;
}

Bishop::~Bishop()
{
}

bool Bishop::isValidMove(const Position& initPos, const Position& finalPos) const
{
    if (initPos == finalPos)
    { 
        return false;
    }

    int diffX = abs(initPos.getX() - finalPos.getX());
    int diffY = abs(initPos.getY() - finalPos.getY());
    if (diffX == diffY)
    {
        return true;
    }

    //This is the rook move.
    if (initPos.getX() == finalPos.getX() ||
        initPos.getY() == finalPos.getY())
    {
        return true;
    }
    return false;
}

std::vector<Position> Bishop::getPath(const Position& initPos, const Position& finalPos) const
{
    std::vector<Position> path;
    int pathLength = (abs(initPos.getX() - finalPos.getX()) +
        abs(initPos.getY() - finalPos.getY())) / 2 + 1;

    //Integer.signum(a) provides the sign of a number 1 if positive and -1 if negative.
    //In this case i am considering initPos as the first point and finalPos as second
    int i_X = Integer.signum(finalPos.getX() - initPos.getX());
    int i_Y = Integer.signum(finalPos.getY() - initPos.getY());

    for (int cnt = 0; cnt < pathLength; cnt++)
    {
        path.push_back(Position(initPos.getX() + i_X * cnt, initPos.getY() + i_Y * cnt));
    }
    return path;
}