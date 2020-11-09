/**
 * Implementation of the BoardManager class
 */

#include "BoardManager.h"


BoardManager::BoardManager() :
    moveList(),
    currentPlayer(UNKNOWN)
{
    board = Board();
}

void BoardManager::resetBoard()
{
    moveList = new ArrayList<Move>();
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

std::list<Move> BoardManager::getMoveList() const
{
    return moveList;
}

Board BoardManager::getBoard() const
{
    return board;
}

bool BoardManager::promote(Square& square, TypeOfPiece::PieceType pieceType) 
{
    if (isValidPromotion(square)) {
        std::shared_ptr<Piece> piece;
        switch (pieceType)
        {
            case TypeOfPiece::PieceType::BISHOP:
                piece = new Bishop(square.getPiece()->getColor());

            case TypeOfPiece::PieceType::KNIGHT:
                piece = new Knight(square.getPiece()->getColor());

            case TypeOfPiece::PieceType::ROOK:
                piece = new Rook(square.getPiece()->getColor());

            case TypeOfPiece::PieceType::QUEEN: //intentional fall through
            default: // default to Queen
                piece = new Queen(square.getPiece()->getColor());
        }
        moveList.push_back(new Move(square.getPosition(), square.getPosition(), piece, square));
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

bool BoardManager::isGameOver() const
{
    if (isCheckmate(WHITE) || isCheckmate(BLACK)) 
    {
        return true;
    }
    return false;
}

bool BoardManager::isCheckmate(Color color) const
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
            if (isValidMove(squareOfKing(color), board.getBoard().at(x).at(y)) &&
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
                    if (tmpSquare.getPiece()->getColor() == kingSquare.getPiece()->getColor() &&
                        isValidMove(tmpSquare, board.getSquare(position))) 
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

    Move lastMove = moveList.get(moveList.size() - 1);
    if (lastMove.getFinalCoordinate() != lastMove.getInitCoordinate()) 
    {
        board.makeMove(lastMove.getFinalCoordinate(),
            lastMove.getInitCoordinate());

        if (lastMove.isCapture())
        {
            board.setPiece(lastMove.getCaptureCoordinate(),
                lastMove.getCapturedPiece());
        }
    }
    else 
    {
        // If the move was a promotion.
        moveList.remove(moveList.size() - 1);
        lastMove = moveList.get(moveList.size() - 1);
        board.setPiece(lastMove.getFinalCoordinate(), new Pawn(lastMove
            .getPiece().getPlayer()));
    }
    // Flush the lastmove.
    moveList.remove(moveList.size() - 1);
    // Switch the current players.
    switchCurrentPlayer();
}

std::vector<Square> BoardManager::getValidMoves(const Position& position) const
{
    std::vector<Square> moves;
    for (int x = 0; x < 8; x++) 
    {
        for (int y = 0; y < 8; y++)
        {
            if (isValidMove(board.getSquare(position), board.getBoard().at(x).at(y)))
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
            Square capture = board.getSquare((moveList.get(moveList.size() - 1).getFinalCoordinate()));
            enpassant(s1, s2);
            switchCurrentPlayer();
            moveList.add(Move(s1.getPosition(), s2.getPosition(), tmp, capture));
            return true;
        }
        else if (isValidMove(s1, s2)) {
            switchCurrentPlayer();
            moveList.add(Move(s1.getPosition(), s2.getPosition(), s1.getPiece(), s1));
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
        Move lastMove = moveList.get(moveList.size() - 1);
        if (lastMove.getPiece() == nullptr) 
        {
            return false;
        }
        if (board.getSquare(lastMove.getFinalCoordinate()).getPiece()->getType() == TypeOfPiece::PieceType::PAWN) 
        {
            // The pawn should be moving two steps forward/backward.
            // And our pawn should be moving to the same file as the last
            // pawn
            if (abs(lastMove.getFinalCoordinate().getY() - lastMove.getInitCoordinate().getY()) == 2 &&
                lastMove.getFinalCoordinate().getX() == finalSquare.getPosition().getX()) {
                return true;
            }
        }
    }
    return false;
}

void BoardManager::enpassant(const Square& initSquare, const Square& finalSquare) 
{
    Move lastMove = moveList.get(moveList.size() - 1);
    board.capturePiece(board.getSquare(lastMove.getFinalCoordinate()));
    board.makeMove(initSquare, finalSquare);
}

bool BoardManager::moveMakesCheck(const Square& initSquare, const Square& finalSquare)
{
    std::shared_ptr<Piece> temporaryPiece = finalSquare.getPiece();
    finalSquare.setPiece(initSquare.getPiece());
    initSquare.releasePiece();
    bool enpassant = false;
    std::shared_ptr<Piece> tmp = nullptr;
    Square lastMove;
    // if it is a enpassant move then you must also remove a piece from the
    // board temporarily.
    if (isValidEnpassant(initSquare, finalSquare)) {
        enpassant = true;
        lastMove = board.getSquare(moveList.get(moveList.size() - 1)
            .getFinalCoordinate());
        tmp = lastMove.getPiece();
        lastMove.releasePiece();
    }

    if (isCheck(finalSquare.getPiece().getPlayer())) {
        initSquare.setPiece(finalSquare.getPiece());
        finalSquare.setPiece(temporaryPiece);
        if (enpassant) {
            lastMove.setPiece(tmp);
        }
        return true;
    }
    else {
        initSquare.setPiece(finalSquare.getPiece());
        finalSquare.setPiece(temporaryPiece);
        if (enpassant) {
            lastMove.setPiece(tmp);
        }
    }
    return false;
}

Square squareOfKing(Color color) {
    Square[][] squares = board.getSquares();
    Square squareOfKing = null;
    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            Square square = squares[x][y];
            if (square.isOccupied()) {
                if (square.getPiece().getType() == PieceType.KING
                    && square.getPiece().getPlayer() == player) {
                    squareOfKing = square;
                }
            }
        }
    }
    return squareOfKing;
}

/**
    * Checks if there is check for the player
    *
    * @param player
    *            Is this player in check
    * @return boolean If the player is in check
    */
public boolean isCheck(PlayerType player) {
    if (getAttackingPieces(player).length > 0) {
        return true;
    }
    else {
        return false;
    }
}

/**
    * Checks if the move is valid pawn capture move
    *
    * @param initSquare
    *            Initial Square
    * @param finalSquare
    *            Final Square
    * @return boolean If the pawn capture is valid
    */
private boolean isValidPawnCapture(Square initSquare, Square finalSquare) {
    // If the piece is not a pawn OR this is not a capture.
    if (!finalSquare.isOccupied()
        || initSquare.getPiece().getType() != PieceType.PAWN) {
        return false;
    }
    Coordinate initPos = initSquare.getCoordinate();
    Coordinate finalPos = finalSquare.getCoordinate();
    PlayerType player = initSquare.getPiece().getPlayer();

    // This is for normal pawn capture moves.
    if (Math.abs(initPos.getY() - finalPos.getY()) == 1
        && Math.abs(initPos.getX() - finalPos.getX()) == 1) {
        // White can only move forward
        if (player == PlayerType.WHITE) {
            if (initPos.getY() < finalPos.getY()) {
                return true;
            }
        }
        // Black can only move backward in a sense.
        if (player == PlayerType.BLACK) {
            if (initPos.getY() > finalPos.getY()) {
                return true;
            }
        }

    }
    return false;
}

/**
    * @param square
    *            The square of the piece
    * @return boolean If this piece has been moved or captured.
    */
private boolean hasPieceMoved(Square square) {
    for (Move move : moveList) {
        if (move.getInitCoordinate() == square.getCoordinate()
            || move.getFinalCoordinate() == square.getCoordinate()) {
            return true;
        }
    }
    return false;
}

/**
    * Checks if it is valid Castling move
    *
    * @param kingSquare
    *            The square of the king
    * @param rookSquare
    *            The square of the rook
    * @return boolean If this is valid Castling
    */
private boolean isValidCastling(Square kingSquare, Square rookSquare) {
    // Check if the squares are occupied.
    if (!(kingSquare.isOccupied() && rookSquare.isOccupied())) {
        return false;
    }
    // Check if the pieces have been moved or not.
    if (hasPieceMoved(kingSquare) || hasPieceMoved(rookSquare)) {
        return false;
    }

    // First check if the move is valid.
    if (!rookSquare.getPiece().isValidMove(kingSquare.getCoordinate(),
        rookSquare.getCoordinate())) {
        return false;
    }
    // Check if the path is clear
    if (!isPathClear(
        rookSquare.getPiece().getPath(rookSquare.getCoordinate(),
            kingSquare.getCoordinate()),
        rookSquare.getCoordinate(), kingSquare.getCoordinate())) {
        return false;
    }
    // Now check if the movement of the castling is fine
    // First check if the piece is king and rook
    if (kingSquare.getPiece().getType() == PieceType.KING
        && rookSquare.getPiece().getType() == PieceType.ROOK) {

        int col = 0;
        if (kingSquare.getPiece().getPlayer() == PlayerType.BLACK) {
            col = 7;
        }
        // The peices are in correct position for castling.

        if (kingSquare.getCoordinate().equals(new Coordinate(4, col))
            && (rookSquare.getCoordinate().equals(
                new Coordinate(0, col)) || rookSquare
                .getCoordinate().equals(new Coordinate(7, col)))) {

            // Check if there is check in any way between the king and final
            // king square
            int offset;
            if (Math.signum(rookSquare.getCoordinate().getX()
                - kingSquare.getCoordinate().getX()) == 1) {
                offset = 2;
            }
            else {
                offset = -2;
            }
            // Calculates final kings X coordinate
            int kingX = kingSquare.getCoordinate().getX() + offset;
            for (Coordinate coordinate : rookSquare.getPiece()
                .getPath(
                    kingSquare.getCoordinate(),
                    new Coordinate(kingX, kingSquare
                        .getCoordinate().getY()))) {
                if (kingSquare.equals(board.getSquare(coordinate))) {
                    // This removes a nasty null pointer exception
                    continue;
                }
                if (moveMakesCheck(kingSquare, board.getSquare(coordinate))) {
                    return false;
                }
            }

            return true;
        }
    }
    return false;
}

/**
    * Makes a castle move.
    * <p>
    * It calls the isValidCastling() first.
    *
    * @param kingSquare
    *            The square of the King
    * @param rookSquare
    *            The square of the Rook
    */
private void castle(Square kingSquare, Square rookSquare) {
    int offset;
    if (Math.signum(rookSquare.getCoordinate().getX()
        - kingSquare.getCoordinate().getX()) == 1) {
        offset = 2;
    }
    else {
        offset = -2;
    }
    int kingX = kingSquare.getCoordinate().getX() + offset;
    int rookX = kingX - offset / 2;
    board.makeMove(kingSquare.getCoordinate(), new Coordinate(kingX,
        kingSquare.getCoordinate().getY()));
    board.makeMove(rookSquare.getCoordinate(), new Coordinate(rookX,
        rookSquare.getCoordinate().getY()));
}

/**
    * Checks if there are any obstacles between the pieces.
    *
    * @param path
    *            The path between the pieces
    * @param initCoordinate
    *            Initial Coordinate to ignore
    * @param finalCoordinate
    *            Final Coordinate to ignore
    * @return boolean Is path clear
    */
private boolean isPathClear(Coordinate[] path, Coordinate initCoordinate,
    Coordinate finalCoordinate) {
    Square[][] squares = board.getSquares();
    for (Coordinate coordinate : path) {
        if ((squares[coordinate.getX()][coordinate.getY()].isOccupied())
            && (!coordinate.equals(initCoordinate))
            && (!coordinate.equals(finalCoordinate))) {
            return false;
        }
    }
    return true;
}

/**
    * Checks trivial movement. If a sane move is being made it returns true.
    * @param initSquare The initial square
    * @param finalSquare The final square
    * @return boolean If a move is sane.
    */
private boolean isSaneMove(Square initSquare, Square finalSquare) {
    //Check if the coordinates are valid
    if (!initSquare.getCoordinate().isValid() || !initSquare.getCoordinate().isValid())
    {
        return false;
    }
    // If the player tries to move a empty square.
    if (!initSquare.isOccupied()) {
        return false;
    }
    // If it is moving to the same square.
    // This is also checked by every piece but still for safety
    if (initSquare.equals(finalSquare)) {
        return false;
    }

    return true;
}

/**
    * Checks if the piece can make a valid movement to the square.
    *
    * @param initSquare
    *            Initial Square
    * @param finalSquare
    *            Final Square
    * @return boolean If movement is valid
    */
private boolean isValidMovement(Square initSquare, Square finalSquare) {
    if (!isSaneMove(initSquare, finalSquare)) {
        return false;
    }
    // If the player tries to take his own piece.
    if (finalSquare.isOccupied()) {
        if (initSquare.getPiece().getPlayer() == finalSquare.getPiece()
            .getPlayer())
            return false;
    }
    // Check all movements here. Normal Moves, Pawn Captures and Enpassant.
    // Castling are handled by the move function itself.
    // If the piece cannot move to the square. No such movement.
    if (!initSquare.getPiece().isValidMove(initSquare.getCoordinate(),
        finalSquare.getCoordinate())
        && !isValidPawnCapture(initSquare, finalSquare)
        && !isValidEnpassant(initSquare, finalSquare)) {
        return false;
    }
    // Pawns cannot capture forward.
    if (initSquare.getPiece().getType() == PieceType.PAWN
        && finalSquare.isOccupied()
        && !isValidPawnCapture(initSquare, finalSquare)) {
        return false;
    }

    // If piece is blocked by other pieces
    Coordinate[] path = initSquare.getPiece().getPath(
        initSquare.getCoordinate(), finalSquare.getCoordinate());
    if (!isPathClear(path, initSquare.getCoordinate(),
        finalSquare.getCoordinate())) {
        return false;
    }
    return true;
}


bool BoardManager::isValidMove(const Square& initSquare, const Square& finalSquare) const 
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