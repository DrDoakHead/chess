/**
 * A board object is a 2 dimensional array of squares
 */

#ifndef BOARD_H
#define BOARD_H

#include "Square.h"
#include <vector>

class Board 
{
  public:

    /**
     * Default Constructor
     */
    Board();

    /*
    * Destructor
    */
    ~Board();

    /**
     * Resets the board to it's original position
     */
    void resetBoard();

    /**
     * Initializes all the squares
     */
    void setSquares();

    /**
     * Initializes and assigns all white Pieces.
     */
    void setWhitePieces();

    /**
     * Initializes and sets all Black Pieces
     */
    void setBlackPieces();

    /**
     * Returns all the squares on the board
     * @return vector of Square A 2 dimensional array of all the Squares
     */
    std::vector<std::vector<Square> > getBoard() const;

    /**
     * This gets the square with a specific position
     * @param position position of the square
     * @return Square The Square object
     */
    Square getSquare(const Position& position) const;

    /**
     * Makes a Move from the start position to the final position
     * @param startPosition The start position
     * @param finalPosition The final position
     */
    void makeMove(const Position& startPosition, const Position& finalPosition);

    /**
     * This makes a move from a square to another. **Move may be invalid**
     * @param initSquare The initial Square.
     * @param finalSquare The final Square
     */
    void makeMove(Square& initSquare, Square& finalSquare);

    /**
     * This set the piece in the specified coordinate
     * @param coordinate Coordinate of the piece
     * @param piece The piece object to be set.
     */
    void setPiece(const Position& position, const std::shared_ptr<Piece>& piece);

    /**
     * Captures the piece that is present in the square.
     * @param square The square of the piece
     */
    void capturePiece(Square& square) const;

    /**
     * This prints the board in the command line.
     */
    void printBoard();

  protected:

      std::vector<std::vector<Square> > board;
};

#endif // BOARD_H