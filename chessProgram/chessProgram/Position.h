/*
	Decleration of the Position class.  This class holds two unsigned integer values
	that represent a position on the board.  The position are between 1-8 inclusive,
	in the x and y directions.  < 1 and > 8 are invalid.
*/

#include <cstdint>

class Position
{
  public:

	/*
	* Default constructor.  Initalize position to invalid (0, 0)
	*/
	Position();

	/*
	* Constructor with the given x and y
	*/
	Position(const uint8_t x, const uint8_t y);

	/*
	* gets this position's x value
	*/
	int8_t getX() const;

	/*
	* sets this position's x value
	*/
	void setX(int8_t x);

	/*
	* gets this position's y value
	*/
	int8_t getY() const;

	/*
	* sets this position's y value
	*/
	void setY(int8_t xy);

	/*
	* operator =
	* assignment operator
	*/
	Position operator=(const Position& rhs);

	/*
	* operator ==
	* equality operator
	*/
	bool operator==(const Position& rhs);

	/*
	* operator !=
	* inequality operator
	*/
	bool operator!=(const Position& rhs);

	/*
	* operator +
	* addition operator
	*/
	Position operator+(const Position& rhs);

	/*
    * operator -
	* subtraction operator
	*/
	Position operator-(const Position& rhs);

  protected:

	/*
	* checks if a value fits on the chessboard
	*/
	bool isNumberValid(const int8_t numToCheck);

	int8_t m_x;  ///< x position, 8 bit signed int to catch negative numbers
	int8_t m_y;  ///< y position, 8 bit signed int to catch negative numbers

};