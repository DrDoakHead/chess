/*
	Decleration of the Rook class.  This piece moves and attacks horizontaly and verticaly
*/

#include "Piece.h"

class Rook : public Piece
{
	/*
	* Default Constructor
	*/
	Rook();

	/*
	* Contructor with position
	*/
	Rook(const Position& currentPosition);

	/*
	* @copydoc Piece::move
	*/
	void move(const Position& endPosition);

	/*
	* @copydoc Piece::isMoveValid
	*/
	bool isMoveValid(const Position& endPosition);
};