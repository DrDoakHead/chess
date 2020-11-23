/**
 * This class represents a move by a piece
 *
 */
#ifndef MOVE_H
#define MOVE_H

#include "Position.h"
#include "Piece.h"
#include "Square.h"
#include <memory>

class Move
{

public:

    /**
     * Creates a move object. Promotions are represented as movement to the same
     * square and the piece represented is the piece to be promoted to.
     *
     * @param initPosition
     *            The initial move position.
     * @param finalPosition
     *            The position of the final move.
     * @param piece
     *            The piece that was moved
     */
    Move(Position initPosition, Position finalPosition, std::shared_ptr<Piece> piece);

    /**
     * Creates a move object. Promotions are represented as movement to the same
     * square and the piece represented is the piece to be promoted to.
     *
     * @param initPosition
     *            The initial move position.
     * @param finalPosition
     *            The position of the final move.
     * @param piece
     *            The piece that was moved
     * @param captureSquare The square of the piece that was captured.
     */
    Move(Position initPosition, Position finalPosition,
        std::shared_ptr<Piece> piece, Square captureSquare);

    /**
     * Returns the initial move position
     *
     * @return Position The initial position
     */
    Position getInitPosition() const;

    /**
     * It returns the final move position
     *
     * @return Position The final position
     */
    Position getFinalPosition() const;

    /**
     * It returns the piece that was moved.
     *
     * @return piece The piece that was moved.
     */
    std::shared_ptr<Piece> getPiece() const;

    /**
     * Checks if the move was a capture
     * @return bool true fi the move was a capture move, else false
     */
    bool isCapture() const;

    /**
     * Returns the piece that was captured when the move was made.
     * @return Returns the captured piece
     */
    std::shared_ptr<Piece> getCapturedPiece() const;

    /**
     * Returns the coordinate of the capture.
     * @return The coordinate were the capture occured.
     */
    Position getCapturePosition() const;

protected:

    Position initPosition;                ///< the initial position of the move
    Position finalPosition;               ///< the final position of the move
    std::shared_ptr<Piece> piece;         ///< the type of piece
    std::shared_ptr<Piece> capturedPiece; ///< the piece that was captured
    Position capturedPosition;            ///< the position of the captured piece
};

#endif // MOVE_H