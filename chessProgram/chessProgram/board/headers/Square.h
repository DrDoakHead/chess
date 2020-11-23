/*
* This class represents a square on a chessboard.  Each square has a color,
* black or white, and a position in x and y space.
*/

#ifndef SQUARE_H
#define SQUARE_H

#include "Piece.h"
#include "Position.h"
#include <string>
#include <memory>
#include <cstdlib>

class Square
{
public:

    /*
    *  Default constructor
    */
    Square();

    /*
    * Destructor
    */
    ~Square();

    /**
     * Creates a new square.
     * @param position The position of the square
     * @param piece The piece that populates the square, NULL if empty
     */
    Square(const Position& position, const std::shared_ptr<Piece>& piece=nullptr);

    /**
     * Returns the position of the square.
     * @return position position of squares
     */
    Position getPosition() const;

    /**
     * Gets the piece contained in the square
     * @return Piece piece contained in the square 
     */
    std::shared_ptr<Piece> getPiece() const;

    /**
     * Equality operator
     * Checks if two square are equal.  Squares are considered equal if they have
     * the same position
     * @param rhs the right hand side to compare to
     * @return bool true if the squares are equal, else false
     */
    bool operator==(const Square& rhs) const;

    /*
     * Inequality operator
     * Checks if two squares are not equal.  Squares are considered not equal if
     * they have different positions
     * @param rhs the right hand side to compare to
     * @return bool true if the squares are equal, else false
     */
    bool operator!=(const Square& rhs) const;

    /**
     * Checks if the square contains a piece
     * @return bool true if square contains a piece, else false
     */
    bool isOccupied() const;

    /**
     * Gets a string representation of the piece on the square
     * @return string String representation of the piece on the square
     */
    std::string getPieceString() const;

    /**
     * Gets a string representation of the position on the square
     * @return string String representation of the position on the square
     */
    std::string getPositionString() const;

    /**
     * Removes any piece that is currently in the square
     */
    void releasePiece();

    /**
     * Sets a piece to the square
     * @param piece The piece object
     */
    void setPiece(const std::shared_ptr<Piece>& piece);

  protected:

      std::shared_ptr<Piece> m_piece;
      Position m_position;
};

#endif // SQUARE_H