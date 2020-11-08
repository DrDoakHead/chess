/*
* This class represents a square on a chessboard.  Each square has a color,
* black or white, and a position in x and y space.
*/

#include "Color.h"
#include "Position.h"


class Square
{
  public:
    Square();
    void setSpace(Square*);
    void setEmpty();
    void setPieceAndColor(Piece, Color);
    Piece getPiece();
    Color getColor();
    void setX(int ex) { x = ex; }
    void setY(int why) { y = why; }
    int getX() { return x; }
    int getY() { return y; }

  protected:

	Color color;
    Position position;
};