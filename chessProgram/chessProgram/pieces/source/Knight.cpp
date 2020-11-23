/**
 * Implementation of the Knight class
 */

#include "Knight.h"

Knight::Knight(Color color)
{
    m_color = color;
    m_typeOfPiece = TypeOfPiece::PieceType::KNIGHT;
}

Knight::~Knight()
{

}

bool Knight::isValidMove(const Position& initPos, const Position& finalPos) const
{
    if (initPos == finalPos)
    { 
        return false;
    }

    int diffX = abs(initPos.getX() - finalPos.getX());
    int diffY = abs(initPos.getY() - finalPos.getY());
    if ((diffX + diffY) == 3 && diffX != 0 && diffY != 0)
    {
        return true;
    }
    return false;
}

std::vector<Position> Knight::getPath(const Position& initPos, const Position& finalPos) const
{
    //The knight can jump over pieces...only look at the end spots
    // @Todo figure out the math on this 
    return std::vector<Position>{ initPos,finalPos };
}