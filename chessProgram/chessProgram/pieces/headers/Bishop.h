/**
 * Methods for the Bishop class
 */

#ifndef BISHOP_H
#define BISHOP_H

#include "Piece.h"

class Bishop : public Piece
{
  public:
    /**
     * Construtor
     * @param color The color the queen belongs to
     */
    Bishop(Color color);

    /*
    * Destructor
    */
    virtual ~Bishop();

    /*
    * Copydoc Piece::isValidMove
    */
    bool isValidMove(const Position& initPos, const Position& finalPos) const;

    /*
    * Copydoc Piece::getPath
    */
    std::vector<Position> getPath(const Position& initPos, const Position& finalPos) const;
};

#endif // !BISHOP_H