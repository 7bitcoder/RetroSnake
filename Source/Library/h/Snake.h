#pragma once
#include <list>
#include <utility>

#include "Board.h"

class Snake
{
  private:
    Direction _movingDir;
    std::list<Coord> _coords;

  public:
    Snake(size_t posX, size_t posY);

    Coord getHeadCoord() const;

    void move(Coord newHeadPos, Direction dir, bool grow = false);

    Direction getDirection() const;

    friend Board &operator<<(Board &board, const Snake &snake);
};
