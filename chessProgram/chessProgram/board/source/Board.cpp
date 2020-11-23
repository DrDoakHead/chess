/*
* Implementation of the Board class
*/

#include "Board.h"
#include "Rook.h"
#include "Bishop.h"
#include "Knight.h"
#include "Pawn.h"
#include "Queen.h"
//#include "King.h"

Board::Board()
{
    setSquares();
    setWhitePieces();
    setBlackPieces();
}

Board::~Board()
{
}

void Board::resetBoard() 
{
    setSquares();
    setWhitePieces();
    setBlackPieces();
}

void Board::setSquares() 
{
    for (int8_t x = 0; x < 8; x++)
    {
        for (int8_t y = 0; y < 8; y++)
        {
            board[x][y] = Square(Position(x, y));
        }
    }
}

void Board::setWhitePieces() 
{
    std::shared_ptr<Rook> rook(new Rook(WHITE));
    std::shared_ptr<Bishop> bishop(new Bishop(WHITE));
    std::shared_ptr<Knight> knight(new Knight(WHITE));
    std::shared_ptr<Pawn> pawn(new Pawn(WHITE));
    std::shared_ptr<Queen> queen(new Queen(WHITE));
    std::shared_ptr<King> king(new King(WHITE));

    board[2][0].setPiece(bishop);
    board[5][0].setPiece(bishop);
    board[1][0].setPiece(knight);
    board[6][0].setPiece(knight);
    board[0][0].setPiece(rook);
    board[7][0].setPiece(rook);
    board[3][0].setPiece(queen);
    board[4][0].setPiece(king);
    board[0][1].setPiece(pawn);
    board[1][1].setPiece(pawn);
    board[2][1].setPiece(pawn);
    board[3][1].setPiece(pawn);
    board[4][1].setPiece(pawn);
    board[5][1].setPiece(pawn);
    board[6][1].setPiece(pawn);
    board[7][1].setPiece(pawn);
}

void Board::setBlackPieces()
{
    std::shared_ptr<Rook> rook(new Rook(BLACK));
    std::shared_ptr<Bishop> bishop(new Bishop(BLACK));
    std::shared_ptr<Knight> knight(new Knight(BLACK));
    std::shared_ptr<Pawn> pawn(new Pawn(BLACK));
    std::shared_ptr<Queen> queen(new Queen(WHITE));
    std::shared_ptr<King> king(new King(WHITE));

    board[2][7].setPiece(bishop);
    board[5][7].setPiece(bishop);
    board[1][7].setPiece(knight);
    board[6][7].setPiece(knight);
    board[0][7].setPiece(rook);
    board[7][7].setPiece(rook);
    board[3][7].setPiece(queen);
    board[4][7].setPiece(king);
    board[0][6].setPiece(pawn);
    board[1][6].setPiece(pawn);
    board[2][6].setPiece(pawn);
    board[3][6].setPiece(pawn);
    board[4][6].setPiece(pawn);
    board[5][6].setPiece(pawn);
    board[6][6].setPiece(pawn);
    board[7][6].setPiece(pawn);
}

std::vector<std::vector<Square> > Board::getBoard() const
{
    return board;
}

Square Board::getSquare(const Position& position) const
{
    Square result;
    for (int8_t x = 0; x < 8; x++)
    {
        for (int8_t y = 0; y < 8; y++) {
            if (board.at(x).at(y).getPosition() == position)
            {
                result = board.at(x).at(y);
            }
        }
    }
    return result;
}

void Board::makeMove(const Position& startPosition, const Position& finalPosition)
{
    Square initSquare = getSquare(startPosition);
    Square finalSquare = getSquare(finalPosition);
    makeMove(initSquare, finalSquare);
}

void Board::makeMove(Square& initSquare, Square& finalSquare)
{
    //Has a piece been captured;
    if (finalSquare.isOccupied())
    {
        capturePiece(finalSquare);
    }
    //Make the move
    finalSquare.setPiece(initSquare.getPiece());
    initSquare.releasePiece();
}

void Board::setPiece(const Position& position, const std::shared_ptr<Piece>& piece)
{
    getSquare(position).setPiece(piece);
}

void Board::capturePiece(Square& square) const
{
    if (square.isOccupied())
    {
        square.releasePiece();
    }
}

void Board::printBoard() 
{/*
    for (int y = 7; y >= 0; y--) 
    {
        for (int x = 0; x < 8; x++)
        {
            System.out.print(board[x][y].getPieceString() + " ");
        }
        System.out.print('\n');
    }*/
}
