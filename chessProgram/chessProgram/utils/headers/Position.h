/*
	Decleration of the Position class.  This class holds two unsigned integer values
	that represent a position on the board.  The position are between 1-8 inclusive,
	in the x and y directions.  < 1 and > 8 are invalid.
*/

#ifndef POSITION_H
#define POSITION_H


#include <cstdint>
#include <string>

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
	Position(const int8_t x, const int8_t y);

	/*
	* Destructor
	*/
	~Position();

	/*
	* gets this position's x value
	*/
	int8_t getX() const;

	/*
	* sets this position's x value
	*/
	void setX(const int8_t x);

	/*
	* gets this position's y value
	*/
	int8_t getY() const;

	/*
	* sets this position's y value
	*/
	void setY(const int8_t xy);

	/*
	* output a string representation of the position
	* @return string string representation of the position
	*/
	std::string toString() const;

	/*
	* operator =
	* assignment operator
	*/
	Position operator=(const Position& rhs);

	/*
	* operator ==
	* equality operator
	*/
	bool operator==(const Position& rhs) const;

	/*
	* operator !=
	* inequality operator
	*/
	bool operator!=(const Position& rhs) const;

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
	bool isNumberValid(const int8_t numToCheck) const;

	int8_t m_x;  ///< x position, 8 bit signed int to catch negative numbers
	int8_t m_y;  ///< y position, 8 bit signed int to catch negative numbers

};

#endif // POSITION_H