/**
 * Methods for the Knight class
 */

#ifndef KNIGHT_H
#define KNIGHT_H

#include "Piece.h"

class Knight : public Piece
{
  public:
    /**
     * Create a Knight
     * @param color The color the Knight belongs to
     */
    Knight(Color color);

    /*
    * Destructor
    */
    virtual ~Knight();

    /*
    * copydoc Piece::isValidMove
    */
    bool isValidMove(const Position& initPos, const Position& finalPos) const;

    /*
    * copydoc Piece::getPath
    */
    std::vector<Position> getPath(const Position& initPos, const Position& finalPos) const;
};

#endif // !KNIGHT_H