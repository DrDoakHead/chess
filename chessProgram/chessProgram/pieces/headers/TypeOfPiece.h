/*
* Class for abstract piece to piece conversions
*/

#ifndef TYPE_OF_PIECE
#define TYPE_OF_PIECE

#include <string>

class TypeOfPiece
{
  public:

    TypeOfPiece();

    ~TypeOfPiece();

    enum PieceType
    {
        UNKNOWN,
        KING,
        KNIGHT,
        ROOK,
        QUEEN,
        BISHOP,
        PAWN
    };

    TypeOfPiece(PieceType type);

    std::string toString() const;

    static std::string toString(PieceType type);

    static PieceType fromString(const std::string& value);

  protected:

      PieceType pieceType;
};


#endif // TYPE_OF_PIECE