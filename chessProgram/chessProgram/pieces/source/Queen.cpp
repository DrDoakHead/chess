/**
 * Implementation of the Queen class
 */

#include "Queen.h"

Queen::Queen(Color color)
{
    m_color = color;
    m_typeOfPiece = TypeOfPiece::PieceType::QUEEN;
}

Queen::~Queen()
{
}

bool Queen::isValidMove(const Position& initPos, const Position& finalPos) const
{
    // The queen's valid moves are a combination of Bishop, Rook, and King
    if (initPos == finalPos) 
    { 
        return false;
    }

    // This is the bishop move
    int diffX = abs(initPos.getX() - finalPos.getX());
    int diffY = abs(initPos.getY() - finalPos.getY());
    if (diffX == diffY)
    {
        return true;
    }

    // This is the rook move
    if (initPos.getX() == finalPos.getX() ||
        initPos.getY() == finalPos.getY())
    {
        return true;
    }

    // This is a king move
    if (diffX + diffY == 1)
    {
        // check if this move will not result in the king 
        // being attacked if so return true 
        return true;
    }

    return false;
}

std::vector<Position> Queen::getPath(const Position& initPos, const Position& finalPos) const
{
    std::vector<Position> path;
    // If it is a rook move
    if (initPos.getX() == finalPos.getX() ||
        initPos.getY() == finalPos.getY())
    {
        int pathLength = abs(initPos.getX() - finalPos.getX())
            + abs(initPos.getY() - finalPos.getY()) + 1;
        for (int cnt = 0; cnt < pathLength; cnt++)
        {
            if (initPos.getX() == finalPos.getX())
            {
                path.push_back(Position(initPos.getX(), std::min(initPos.getY(), finalPos.getY()) + cnt));
            }
            else
            {
                path.push_back(Position(std::min(initPos.getX(), finalPos.getX()) + cnt, initPos.getY()));;
            }
        }

    }
    else if (abs(initPos.getX() - finalPos.getX() == abs(initPos.getY() - finalPos.getY())))
    {
        //If it a bishop move.
        int pathLength = (abs(initPos.getX() - finalPos.getX()) +
            abs(initPos.getY() - finalPos.getY())) / 2 + 1;

        //Integer.signum(a) provides the sign of a number 1 if positive and -1 if negative.
        //In this case i am considering initPos as the first point and finalPos as second
        int i_X = sgn(finalPos.getX() - initPos.getX());
        int i_Y = sgn(finalPos.getY() - initPos.getY());

        for (int cnt = 0; cnt < pathLength; cnt++)
        {
            path.push_back(Position(initPos.getX() + i_X * cnt, initPos.getY() + i_Y * cnt));
        }
    }
    else
    {
    }

    return path;
}