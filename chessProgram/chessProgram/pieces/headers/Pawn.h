/**
 * Methods of the Pawn class
 */

#ifndef PAWN_H
#define PAWN_H

#include "Piece.h"

class Pawn : public Piece
{
public:
    /**
     * Construtor
     * @param color - The color the piece belongs to
     */
    Pawn(Color Color);

    /*
    * Destructor
    */
    virtual ~Pawn();

    /*
    * copydoc Piece::isValidMove
    */
    bool isValidMove(const Position& initPos, const Position& finalPos) const;

    /*
    * copydoc Piece::getPath
    */
    std::vector<Position> getPath(const Position& initPos, const Position& finalPos) const;
};

#endif // PAWN_H
