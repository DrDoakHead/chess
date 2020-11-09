/*
	Decleration of the Rook class.  This piece moves and attacks horizontaly and verticaly
*/

#ifndef ROOK_H
#define ROOK_H

#include "Piece.h"
#include <string>

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
	* Destructor
	*/
	~Rook();

	/*
	* get the string value of the piece
	* @return ROOK
	*/
	static std::string toString();

	/*
	* @copydoc Piece::move
	*/
	void move(const Position& endPosition) const;

	/*
	* @copydoc Piece::isMoveValid
	*/
	bool isMoveValid(const Position& endPosition) const;
};

#endif // ROOK_H