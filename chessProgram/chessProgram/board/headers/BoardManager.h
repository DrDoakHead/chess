/*
* This is the class for managing the board.  Most of the magic happens here.  This class
* is responsible for moving pieces, determining if a player is in check, determining if
* a player is checkmated, converting pawns to removed units 
*/

#ifndef BOARD_MANAGER_H
#define BOARD_MANAGER_H

#include "Board.h"
#include "TypeOfPiece.h"
#include "Position.h"
#include "Move.h"
#include <vector>

class BoardManager 
{
  public:

    /**
     * Constructor
     */
     BoardManager();

     /*
     * Destructor
     */
     ~BoardManager();

    /**
     * Resets the board to it's initial state
     */
     void resetBoard();

    /**
     * Switches the player currently to move.
     */
     void switchCurrentPlayer();

    /**
     * Return the player who is to move
     *
     * @return Color the current player's color
     */
    Color getCurrentPlayer() const;

    /**
     * Returns a list of moves that the player has made.
     *
     * @return List The list of moves
     */
    std::vector<Move> getMoveList() const;

    /**
     * Returns the board object
     *
     * @return board The board object
     */
    Board getBoard() const;

    /**
     * Promotes a pawn to a newer piece. Calls isValidPromotion function first
     *
     * @param square - promotion square - this will be updated to add new piece
     * @param pieceType - the type of piece to promote to. Default to QUEEN.
     * @return boolean If the promotion was made
     */
    bool promote(Square& square, TypeOfPiece::PieceType pieceType=TypeOfPiece::QUEEN);

    /**
     * Checks if the square contains a pawn that can be promoted.
     *
     * @param square - square to check
     * @return bool true if the pawn can be promoted, false if not
     */
    bool isValidPromotion(const Square& square) const;

    /**
     * Returns if either of the players are checkmated.
     *
     * @return boolean true if gameOver, else false
     */
    bool isGameOver();

    /**
     * Returns if the color is checkmated or not.
     *
     * @param color - the color to check checkmate for
     * @return bool true if checkmate, else false
     */
    bool isCheckmate(Color color);

    /**
     * This undoes the previous move.
     */
    void undoMove();

    /**
     * This function returns all the valid moves a square/piece can make
     *
     * @param position - the position of the current piece
     * @return vector of squares of possible squares
     */
    std::vector<Square> getValidMoves(const Position& position);

    /**
     * Returns the array of squares of the pieces that are attacking the King If
     * no piece is attacking it then empty array is returned.
     *
     * @param color - the color whose king is under attack
     * @return Squares[] The vector of squares of pieces that are attacking the KING
     * @Note Max Size of array is 2
     */
    std::vector<Square> getAttackingPieces(Color color) const;

    /**
     * Makes a move from initial coordinate to final one. It calls
     * isValidMove(),isValidCastling() and isValidEnpassant()
     *
     * @param startPosition - starting position
     * @param finalPosition - final position
     * @return boolean If the move was made
     */
    bool move(const Position& startPosition, const Position& finalPosition);

    /**
     * Checks if the move is valid enpassant move.
     *
     * @param initSquare - initial Square
     * @param finalSquare - final Square
     * @return bool true if valid move, else false
     */
    bool isValidEnpassant(const Square& initSquare, const Square& finalSquare) const;

    /**
     * Makes a Enpassant move
     *
     * @param initSquare - initial Square
     * @param finalSquare - final Square
     */
    void enpassant(const Square& initSquare, const Square& finalSquare);

    /**
     * Checks if the given move makes check for the moving player
     *
     * @param initSquare - initial Square
     * @param finalSquare - final Square
     * @return bool true if the move makes check, else false
     */
    bool moveMakesCheck(Square& initSquare, Square& finalSquare);

    /**
     * Gets the square of the King
     *
     * @param color - The color of the king
     * @return Square The square of the king
     */
    Square squareOfKing(Color color) const;

    /**
     * Checks if there is check for the player
     *
     * @param color - is this color in check
     * @return bool true if the color is in check, else false
     */
    bool isCheck(Color color) const;

    /**
     * Checks if the move is valid pawn capture move
     *
     * @param initSquare - initial Square
     * @param finalSquare - final Square
     * @return bool true if the pawn capture is valid, else false
     */
    bool isValidPawnCapture(const Square& initSquare, const Square& finalSquare) const;

    /**
     * @param square - the square of the piece
     * @return bool true if this piece has been moved or captured, else false
     */
    bool hasPieceMoved(const Square& square) const;

    /**
     * Checks if it is valid Castling move
     *
     * @param kingSquare - the square of the king
     * @param rookSquare - the square of the rook
     * @return bool true if this is valid Castling, else false
     */
    bool isValidCastling(Square& kingSquare, Square& rookSquare);

    /**
     * Makes a castle move.
     * @Note calls the isValidCastling() first
     *
     * @param kingSquare - the square of the King
     * @param rookSquare - the square of the Rook
     */
    void castle(const Square& kingSquare, const Square& rookSquare);

    /**
     * Checks if there are any obstacles between the pieces.
     *
     * @param path - the path between the pieces as a vector of positions
     * @param initPosition - initial position to ignore
     * @param finalPosition - final position to ignore
     * @return bool true if the path is clear, else false
     */
    bool isPathClear(const std::vector<Position>& path, 
        const Position& initPosition, const Position& finalCoordinate) const;

    /**
     * Checks trivial movement. If a sane move is being made it returns true.
     * @param initSquare - the initial square
     * @param finalSquare - the final square
     * @return bool true if a move is valid, false if invalid
     */
    bool isSaneMove(const Square& initSquare, const Square& finalSquare) const;

    /**
     * Checks if the piece can make a valid movement to the square.
     * @param initSquare - initial Square
     * @param finalSquare - final Square
     * @return bool true if move is valid, else false
     */
    bool isValidMovement(const Square& initSquare, const Square& finalSquare) const;

    /**
     * Checks if the given move is valid and safe. Calls the isValidMovement()
     * and moveMakesCheck().
     *
     * @param initSquare - the initial Square
     * @param finalSquare - the final Square
     * @return bool true if move is valid, else false
     */
    bool isValidMove(Square& initSquare, Square& finalSquare);

    template <typename T> int sgn(T val)
    {
        return (T(0) < val) - (val < T(0));
    }

  protected:

    Board board;                ///< the board in play
    Color currentPlayer;        ///< color of the active player
    std::vector<Move> moveList; ///< list of moves taken
};

#endif // BOARD_MANAGER_H