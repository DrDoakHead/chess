/*
*  Definition of the Rook class.
*/

#include "Rook.h"

Rook::Rook()
{
	//@TODO auto-gen constructor
}

Rook::Rook(const Position& currentPosition)
{
	m_currentPosition = currentPosition;
}

bool Rook::isMoveValid(const Position& endPosition)
{
    // Attempt to move to the same cell
    if (m_currentPosition == endPosition)
    {
        return false;
    }

    // Collision detection
    if (m_currentPosition.getX() == endPosition.getX())
    {
        // Move horizontal
        if (m_currentPosition.getY() < endPosition.getY()) 
        {
            // Move right
            for (int8_t i = m_currentPosition.getY() + 1; i <= endPosition.getY(); ++i)
            {
                if (pieceAt(m_currentPosition.getX(), i) != EMPTY)
                {
                    return false;
                }
            }
        }
        else
        {
            // Move left
            for (int8_t i = m_currentPosition.getY() - 1; i >= endPosition.getY(); --i)
            {
                if (pieceAt(m_currentPosition.getX(), i) != EMPTY)
                {
                    return false;
                }
            }
        }
    }
    else if (m_currentPosition.getY() == endPosition.getY()) 
    {
        // Move vertical
        if (m_currentPosition.getX() < endPosition.getX()) 
        {
            // Move down
            for (int8_t i = m_currentPosition.getX() + 1; i <= endPosition.getX(); ++i)
            {
                if (pieceAt(i, m_currentPosition.getY()) != EMPTY)
                {
                    return false;
                }
            }
        }
        else 
        {
            // Move up
            for (int8_t i = m_currentPosition.getX() - 1; i >= endPosition.getX(); --i)
            {
                if (pieceAt(i, m_currentPosition.getY()) != EMPTY)
                {
                    return false;
                }
            }
        }
    }
    else
    {
        // Not horizontal or vertical
        return false;
    }
    return true;
}

void Rook::move(const Position& endPosition)
{
    if (isMoveValid(endPosition))
    {

    }

}