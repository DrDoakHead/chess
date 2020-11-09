/*
* The playerType class is used to abstanciate a "player" as a certain color
*/

#ifndef PLAYER_TYPE
#define PLAYER_TYPE

#include "Color.h"
#include <string>

class PlayerType
{
  public:

    PlayerType(const std::string& value)
    {
        this.value = value;
    }

    std::string toString()

  protected:
    std::string value;
};

#endif // PLAYER_TYPE