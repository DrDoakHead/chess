/*
	Decleration of the Piece class.  This is to be the abstract base class for all pieces
	to inherit from.  It contains the logic that all pieces will have, and pure virtual
	functions that the pieces need to implement.
*/

#ifndef PIECE_H
#define PIECE_H

#include "Color.h"
#include "Position.h"
#include "TypeOfPiece.h"


class Piece
{
  public:

	/*
	* Default Constructor
	*/
	Piece();

	/*
	* Destructor
	*/
	virtual ~Piece();

	/*
	* Construct a piece with the specified color
	*/
	Piece(Color color);
	  
	/*
	 * gets the color of the piece
	 * @return color - the color of the piece
	 */
	Color getColor() const;

	/*
	 * sets the color of the piece
	 * @param color - the color to set the piece to
	 */
	void setColor(Color color);

	/*
	* gets the type of piece.  This will trigger the derived class
	* to return its type
	*/
	virtual TypeOfPiece::PieceType getType() const;

  protected:
	
	Color m_color;
	Position m_currentPosition;
};

#endif // PIECE_H