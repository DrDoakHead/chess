
/*
* Implementation of the Pawn class
*/

#include "Pawn.h"

Pawn::Pawn(Color color)
{
    m_color = color;
    m_typeOfPiece = TypeOfPiece::PieceType::PAWN;
}

Pawn::~Pawn()
{
}

bool Pawn::isValidMove(const Position& initPos, const Position& finalPos) const
{
    if (initPos == finalPos)
    {
        return false;
    }
    // This is for normal pawn moves.
    if (abs(initPos.getY() - finalPos.getY()) == 1 &&
        abs(initPos.getX() - finalPos.getX()) == 0)
    {
        // White can only move forward
        if (m_color == WHITE)
        {
            if (initPos.getY() < finalPos.getY())
            {
                return true;
            }
        }
        // Black can only move "backwards" with aspect to the board
        else if (m_color == BLACK)
        {
            if (initPos.getY() > finalPos.getY())
            {
                return true;
            }
        }
        else {/*No else case*/ }
    }

    // This is for first pawn move
    if (abs(initPos.getY() - finalPos.getY()) == 2 &&
        abs(initPos.getX() - finalPos.getX()) == 0 &&
        (initPos.getY() == 1 || initPos.getY() == 6))
    {
        // White can only move forward
        if (m_color == WHITE)
        {
            if (initPos.getY() < finalPos.getY())
            {
                return true;
            }
        }
        // Black can only move backward in a sense.
        else if (m_color == BLACK)
        {
            if (initPos.getY() > finalPos.getY())
            {
                return true;
            }
        }
        else{/*No else class*/ }
    }

    // This if for normal pawn captures.
    //@ Todo
    // this is for Enpassant.
    //@ Todo

    return false;
}

std::vector<Position> Pawn::getPath(const Position& initPos, const Position& finalPos) const
{
    // This is for pawn captures
    if (initPos.getX() != finalPos.getX())
    { 
        return std::vector<Position>{initPos, finalPos}; 
    }
    // This is for normal pawn moves and first pawn moves
    int pathLength = abs(initPos.getY() - finalPos.getY()) + 1;
    std::vector<Position> path;
    for (int cnt = 0; cnt < pathLength; cnt++) {
        path.push_back(Position(initPos.getX(), std::min(initPos.getY(), finalPos.getY()) + cnt));
    }
    return path;
}