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
#include <vector>


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
	Piece(Color color, TypeOfPiece::PieceType pieceType);
	  
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
	* gets the string representation of the piece
	* @return string representation of the piece
	*/
	virtual std::string toString() const;

	/*
	* gets the type of piece.  This will trigger the derived class
	* to return its type
	*/
	virtual TypeOfPiece::PieceType getType() const;

	/**
	* Checks if the move is a valid move by the piece.
	* @param initPos Initial Coordinate
	* @param finalPos Final Coordinate
	* @return bool true if the move is valid, else false
	*/
	virtual bool isValidMove(const Position& initPos, const Position& finalPos) const = 0;

	/**
	 * Return the path for movement.
	 * @param initPos The initial Coordinate
	 * @param finalPos The final Coordinate
	 * @return vector of positions - the Path for the movement
	 */
	virtual std::vector<Position> getPath(const Position& initPos, const Position& finalPos) const = 0;

  protected:
	
	Color m_color;
	TypeOfPiece::PieceType m_typeOfPiece;
};

#endif // PIECE_H