/**
 * Implementation of the BoardManager class
 */

#include "BoardManager.h"
#include "Rook.h"
#include "Bishop.h"
#include "Knight.h"
#include "Queen.h"
#include "Pawn.h"

BoardManager::BoardManager() :
    moveList(),
    currentPlayer(UNKNOWN)
{
    board = Board();
}

BoardManager::~BoardManager()
{

}

void BoardManager::resetBoard()
{
    moveList.clear();
    board.resetBoard();
    currentPlayer = WHITE;
}

void BoardManager::switchCurrentPlayer() 
{
    if (currentPlayer == WHITE) 
    {
        currentPlayer = BLACK;
    }
    else 
    {
        currentPlayer = WHITE;
    }
}

Color BoardManager::getCurrentPlayer() const
{
    return currentPlayer;
}

std::vector<Move> BoardManager::getMoveList() const
{
    return moveList;
}

Board BoardManager::getBoard() const
{
    return board;
}

bool BoardManager::promote(Square& square, TypeOfPiece::PieceType pieceType) 
{
    if (isValidPromotion(square))
    {
        std::shared_ptr<Piece> piece;
        std::shared_ptr<Rook> rook;
        std::shared_ptr<Bishop> bishop;
        std::shared_ptr<Knight> knight;
        std::shared_ptr<Queen> queen;
        piece->setColor(square.getPiece()->getColor());
        switch (pieceType)
        {
            case TypeOfPiece::PieceType::BISHOP:
                piece = bishop;

            case TypeOfPiece::PieceType::KNIGHT:
                piece = knight;

            case TypeOfPiece::PieceType::ROOK:
                piece = rook;

            case TypeOfPiece::PieceType::QUEEN:
            default: // default to Queen
                piece = queen;
        }
        moveList.push_back(Move(square.getPosition(), square.getPosition(), piece, square));
        square.setPiece(piece);
        return true;
    }
    return false;
}

bool BoardManager::isValidPromotion(const Square& square) const
{
    if (!square.isOccupied() == true) 
    {
        return false;
    }
    if (square.getPiece()->getType() == TypeOfPiece::PieceType::PAWN)
    {
        int col = 7;
        if (square.getPiece()->getColor() == BLACK) 
        {
            col = 0;
        }
        if (square.getPosition() == Position(square.getPosition().getX(), col))
        {
            return true;
        }

    }
    return false;
}

bool BoardManager::isGameOver()
{
    if (isCheckmate(WHITE) || isCheckmate(BLACK)) 
    {
        return true;
    }
    return false;
}

bool BoardManager::isCheckmate(Color color)
{
    std::vector<Square> attackers = getAttackingPieces(color);

    // If there are no attackers
    if (attackers.size() == 0) 
    {
        return false;
    }

    // If there is more than one attacker then there are many options check all.
    bool checkmate = true;
    Square attackerSquare = attackers.at(0);
    Square kingSquare = squareOfKing(color);
    std::vector<Position> attackPath = attackerSquare.getPiece()->getPath(
        attackerSquare.getPosition(), kingSquare.getPosition());
    std::vector<std::vector<Square> > allSquares = board.getBoard();
    for (int x = 0; x < 8; x++) 
    {
        for (int y = 0; y < 8; y++)
        {
            // If the king can move to a different square.
            Square square = squareOfKing(color);
            if (isValidMove(square, board.getBoard().at(x).at(y)) &&
                squareOfKing(color) != board.getBoard().at(x).at(y)) 
            {
                return false;
            }
            for (Position position : attackPath) 
            {
                Square tmpSquare = allSquares.at(x).at(y);
                // The square must be occupied
                if (tmpSquare.isOccupied()) {
                    // The player must move his own piece between the paths
                    // of the attacker and the King.
                    // If it can do so then there is no checkmate
                    Square square = board.getSquare(position);
                    if (tmpSquare.getPiece()->getColor() == kingSquare.getPiece()->getColor() &&
                        isValidMove(tmpSquare, square))
                    {
                        checkmate = false;
                    }
                }
            }
        }
    }
    return checkmate;
}

void BoardManager::undoMove() 
{
    if (moveList.empty()) 
    {
        return;
    }

    Move lastMove = moveList.at(moveList.size() - 1);
    if (lastMove.getFinalPosition() != lastMove.getInitPosition()) 
    {
        board.makeMove(lastMove.getFinalPosition(), lastMove.getInitPosition());

        if (lastMove.isCapture())
        {
            board.setPiece(lastMove.getCapturePosition(), lastMove.getCapturedPiece());
        }
    }
    else 
    {
        // If the move was a promotion.
        moveList.pop_back();
        lastMove = moveList.at(moveList.size() - 1);
        std::shared_ptr<Pawn> pawn(new Pawn(lastMove.getPiece()->getColor()));
        board.setPiece(lastMove.getFinalPosition(), pawn);
    }
    // Flush the lastmove.
    moveList.pop_back();
    // Switch the current players.
    switchCurrentPlayer();
}

std::vector<Square> BoardManager::getValidMoves(const Position& position)
{
    std::vector<Square> moves;
    for (int x = 0; x < 8; x++) 
    {
        for (int y = 0; y < 8; y++)
        {
            Square square = board.getSquare(position);
            if (isValidMove(square, board.getBoard().at(x).at(y)))
            {
                moves.push_back(board.getBoard().at(x).at(y));
            }
        }
    }
    return moves;
}

std::vector<Square> BoardManager::getAttackingPieces(Color color) const
{
    std::vector<Square> squares;
    std::vector<std::vector<Square> > allSquares = board.getBoard();
    Square kingSquare = squareOfKing(color);
    for (int x = 0; x < 8; x++) 
    {
        for (int y = 0; y < 8; y++)
        {
            Square tmpSquare = allSquares.at(x).at(y);
            if (tmpSquare.isOccupied()) 
            {
                if (isValidMovement(tmpSquare, kingSquare) &&
                    kingSquare.getPiece()->getColor() != tmpSquare.getPiece()->getColor()) 
                {
                    squares.push_back(tmpSquare);
                }
            }

        }
    }
    return squares;
}

bool BoardManager::move(const Position& initPosition, const Position& finalPosition) 
{
    // only move to and from valid positions
    if (initPosition == Position() || finalPosition == Position()) 
    { 
        return false; 
    }

    Square s1 = board.getSquare(initPosition);
    Square s2 = board.getSquare(finalPosition);
    //Checks for sane moves
    if (!isSaneMove(s1, s2)) 
    { 
        return false; 
    }
    // Only the current player can move the piece.
    if (currentPlayer == s1.getPiece()->getColor())
    {
        if (isValidCastling(s1, s2)) 
        {
            std::shared_ptr<Piece> tmp = s1.getPiece();
            castle(s1, s2);
            switchCurrentPlayer();
            moveList.push_back(Move(s1.getPosition(), s2.getPosition(), tmp));
            return true;
        }
        else if (isValidEnpassant(s1, s2)) 
        {
            std::shared_ptr<Piece> tmp = s1.getPiece();
            Square capture = board.getSquare((moveList.at(moveList.size() - 1).getFinalPosition()));
            enpassant(s1, s2);
            switchCurrentPlayer();
            moveList.push_back(Move(s1.getPosition(), s2.getPosition(), tmp, capture));
            return true;
        }
        else if (isValidMove(s1, s2)) {
            switchCurrentPlayer();
            moveList.push_back(Move(s1.getPosition(), s2.getPosition(), s1.getPiece(), s1));
            board.makeMove(s1, s2);
            return true;
        }
    }
    return false;
}

bool BoardManager::isValidEnpassant(const Square& initSquare, const Square& finalSquare) const
{
    // The final square should be empty
    if (finalSquare.isOccupied())
    {
        return false;
    }

    // The first piece should be a pawn.
    if (initSquare.getPiece()->getType() != TypeOfPiece::PieceType::PAWN)
    {
        return false;
    }
    // Move type is different according to player color
    if (initSquare.getPiece()->getColor() == WHITE) 
    {
        if (initSquare.getPosition().getY() > finalSquare.getPosition().getY())
        {
            // White can only move forward
            return false;
        }
    }
    else
    {
        if (initSquare.getPosition().getY() < finalSquare.getPosition().getY())
        {
            // Black can only move backward
            return false;
        }
    }
    // The move should be like a bishop move but to a single square.
    if (abs(initSquare.getPosition().getX() - finalSquare.getPosition().getX()) == 1 &&
        abs(initSquare.getPosition().getY() - finalSquare.getPosition().getY()) == 1) 
    {
        // There should be a pawn move before enpassant.
        if (moveList.empty()) 
        {
            return false;
        }
        Move lastMove = moveList.at(moveList.size() - 1);
        if (lastMove.getPiece() == nullptr) 
        {
            return false;
        }
        if (board.getSquare(lastMove.getFinalPosition()).getPiece()->getType() == TypeOfPiece::PieceType::PAWN) 
        {
            // The pawn should be moving two steps forward/backward.
            // And our pawn should be moving to the same file as the last pawn
            if (abs(lastMove.getFinalPosition().getY() - lastMove.getInitPosition().getY()) == 2 &&
                lastMove.getFinalPosition().getX() == finalSquare.getPosition().getX())
            {
                return true;
            }
        }
    }
    return false;
}

void BoardManager::enpassant(const Square& initSquare, const Square& finalSquare) 
{
    Move lastMove = moveList.at(moveList.size() - 1);
    Square square = board.getSquare(lastMove.getFinalPosition());
    board.capturePiece(square);
    board.makeMove(initSquare, finalSquare);
}

bool BoardManager::moveMakesCheck(Square& initSquare, Square& finalSquare)
{
    std::shared_ptr<Piece> temporaryPiece = finalSquare.getPiece();
    finalSquare.setPiece(initSquare.getPiece());
    initSquare.releasePiece();
    bool enpassant = false;
    std::shared_ptr<Piece> tmp = nullptr;
    Square lastMove;
    // if it is a enpassant move then you must also remove a piece from the
    // board temporarily.
    if (isValidEnpassant(initSquare, finalSquare)) 
    {
        enpassant = true;
        lastMove = board.getSquare(moveList.at(moveList.size() - 1).getFinalPosition());
        tmp = lastMove.getPiece();
        lastMove.releasePiece();
    }

    if (isCheck(finalSquare.getPiece()->getColor())) 
    {
        initSquare.setPiece(finalSquare.getPiece());
        finalSquare.setPiece(temporaryPiece);
        if (enpassant) 
        {
            lastMove.setPiece(tmp);
        }
        return true;
    }
    else 
    {
        initSquare.setPiece(finalSquare.getPiece());
        finalSquare.setPiece(temporaryPiece);
        if (enpassant)
        {
            lastMove.setPiece(tmp);
        }
    }
    return false;
}

Square BoardManager::squareOfKing(Color color) const
{
    std::vector<std::vector<Square> > squares = board.getBoard();
    Square squareOfKing;
    for (int x = 0; x < 8; x++) 
    {
        for (int y = 0; y < 8; y++) 
        {
            Square square = squares[x][y];
            if (square.isOccupied()) 
            {
                if (square.getPiece()->getType() == TypeOfPiece::PieceType::KING &&
                    square.getPiece()->getColor() == color) 
                {
                    squareOfKing = square;
                }
            }
        }
    }
    return squareOfKing;
}

bool BoardManager::isCheck(Color color) const
{
    if (getAttackingPieces(color).size() > 0)
    {
        return true;
    }
    else 
    {
        return false;
    }
}

bool BoardManager::isValidPawnCapture(const Square& initSquare, const Square& finalSquare) const
{
    // If the piece is not a pawn OR this is not a capture.
    if (!finalSquare.isOccupied() || 
        initSquare.getPiece()->getType() != TypeOfPiece::PieceType::PAWN)
    {
        return false;
    }
    Position initPos = initSquare.getPosition();
    Position finalPos = finalSquare.getPosition();
    Color color = initSquare.getPiece()->getColor();

    // This is for normal pawn capture moves.
    if (abs(initPos.getY() - finalPos.getY()) == 1 &&
        abs(initPos.getX() - finalPos.getX()) == 1) 
    {
        // White can only move forward
        if (color == Color::WHITE) 
        {
            if (initPos.getY() < finalPos.getY())
            {
                return true;
            }
        }
        // Black can only move "backward"
        if (color == Color::BLACK) {
            if (initPos.getY() > finalPos.getY()) 
            {
                return true;
            }
        }
    }
    return false;
}

bool BoardManager::hasPieceMoved(const Square& square) const
{
    for (Move move : moveList) 
    {
        if (move.getInitPosition() == square.getPosition() ||
            move.getFinalPosition() == square.getPosition())
        {
            return true;
        }
    }
    return false;
}

bool BoardManager::isValidCastling(Square& kingSquare, Square& rookSquare)
{
    // Check if the squares are occupied.
    if (!(kingSquare.isOccupied() && rookSquare.isOccupied()))
    {
        return false;
    }
    // Check if the pieces have been moved or not.
    if (hasPieceMoved(kingSquare) || hasPieceMoved(rookSquare))
    {
        return false;
    }

    // First check if the move is valid.
    if (!rookSquare.getPiece()->isValidMove(kingSquare.getPosition(),
        rookSquare.getPosition()))
    {
        return false;
    }
    // Check if the path is clear
    if (!isPathClear(rookSquare.getPiece()->getPath(rookSquare.getPosition(), kingSquare.getPosition()),
        rookSquare.getPosition(), kingSquare.getPosition())) 
    {
        return false;
    }
    // Now check if the movement of the castling is fine
    // First check if the piece is king and rook
    if (kingSquare.getPiece()->getType() == TypeOfPiece::PieceType::KING &&
        rookSquare.getPiece()->getType() == TypeOfPiece::PieceType::ROOK) 
    {
        int col = 0;
        // column zero for white, 7 for black
        if (kingSquare.getPiece()->getColor() == Color::BLACK)
        {
            col = 7;
        }
        // Check the peices are in correct position for castling
        if (kingSquare.getPosition() == Position(4, col) &&
           (rookSquare.getPosition() == Position(0, col) || 
            rookSquare.getPosition() == Position(7, col))) 
        {
            // Check if there is check in any way between the king and final king square
            int offset;
            if (sgn(rookSquare.getPosition().getX() - kingSquare.getPosition().getX()) == 1) 
            {
                offset = 2;
            }
            else 
            {
                offset = -2;
            }
            // Calculates final kings X coordinate
            int kingX = kingSquare.getPosition().getX() + offset;
            for (Position position : rookSquare.getPiece()->getPath(
                kingSquare.getPosition(), Position(kingX, kingSquare.getPosition().getY()))) 
            {
                // NASTY nullptr exeception
                Square square = board.getSquare(position);
                if (kingSquare == square)
                {
                    continue;
                }
                if (moveMakesCheck(kingSquare, square))
                {
                    return false;
                }
            }
            return true;
        }
    }
    return false;
}

void BoardManager::castle(const Square& kingSquare, const Square& rookSquare)
{
    int offset;
    if (sgn(rookSquare.getPosition().getX() - kingSquare.getPosition().getX()) == 1)
    {
        offset = 2;
    }
    else
    {
        offset = -2;
    }
    int kingX = kingSquare.getPosition().getX() + offset;
    int rookX = kingX - offset / 2;
    board.makeMove(kingSquare.getPosition(), Position(kingX,
        kingSquare.getPosition().getY()));
    board.makeMove(rookSquare.getPosition(), Position(rookX,
        rookSquare.getPosition().getY()));
}

bool BoardManager::isPathClear(const std::vector<Position>& path, 
    const Position& initCoordinate,
    const Position& finalCoordinate) const
{
    std::vector<std::vector<Square> > squares = board.getBoard();
    for (Position position : path) {
        if ((squares.at(position.getX()).at(position.getY()).isOccupied())
            && (position != initCoordinate)
            && (position != finalCoordinate)) 
        {
            return false;
        }
    }
    return true;
}

bool BoardManager::isSaneMove(const Square& initSquare, const Square& finalSquare) const
{
    // If the player tries to move a empty square.
    if (!initSquare.isOccupied()) 
    {
        return false;
    }
    // If it is moving to the same square.
    // This is also checked by every piece but still for safety
    if (initSquare == finalSquare)
    {
        return false;
    }
    return true;
}

bool BoardManager::isValidMovement(const Square& initSquare, const Square& finalSquare) const
{
    if (!isSaneMove(initSquare, finalSquare)) 
    {
        return false;
    }
    // If the player tries to take his own piece.
    if (finalSquare.isOccupied())
    {
        if (initSquare.getPiece()->getColor() == finalSquare.getPiece()->getColor())
        {
            return false;
        }
    }
    // Check all movements here. Normal Moves, Pawn Captures and Enpassant.
    // Castling are handled by the move function itself.
    // If the piece cannot move to the square. No such movement.
    if (!initSquare.getPiece()->isValidMove(initSquare.getPosition(),
        finalSquare.getPosition()) &&
        !isValidPawnCapture(initSquare, finalSquare) &&
        !isValidEnpassant(initSquare, finalSquare)) {
        return false;
    }
    // Pawns cannot capture forward.
    if (initSquare.getPiece()->getType() == TypeOfPiece::PieceType::PAWN &&
       finalSquare.isOccupied() &&
       !isValidPawnCapture(initSquare, finalSquare))
    {
        return false;
    }

    // If piece is blocked by other pieces
    std::vector<Position> path = initSquare.getPiece()->getPath(
        initSquare.getPosition(), finalSquare.getPosition());
    if (!isPathClear(path, initSquare.getPosition(),
        finalSquare.getPosition()))
    {
        return false;
    }
    return true;
}

bool BoardManager::isValidMove(Square& initSquare, Square& finalSquare)
{
    if (isValidCastling(initSquare, finalSquare))
    {
        return true;
    }
    if (!isValidMovement(initSquare, finalSquare))
    {
        return false;
    }
    if (moveMakesCheck(initSquare, finalSquare))
    {
        return false;
    }
    return true;
}