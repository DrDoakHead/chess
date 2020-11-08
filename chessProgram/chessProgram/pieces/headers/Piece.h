/*
	Decleration of the Piece class.  This is to be the abstract base class for all pieces
	to inherit from.  It contains the logic that all pieces will have, and pure virtual
	functions that the pieces need to implement.
*/

#include "Color.h"
#include "Position.h"


class Piece
{
  public:
	  
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
	 * determine if move is valid by comparing the current position to the end position
	 */
	virtual bool isMoveValid(const Position& endPosition) = 0;

	/*
	* move the piece from the start position to the end position
	*/
	virtual void move(const Position& endPosition) = 0;

  protected:
	
	Color m_color;
	Position m_currentPosition;
};
