#pragma once
#include <list>
#include <utility>

#include "Board.h"
#include "IDrawable.h"

class Snake : public IDrawable
{
  private:
    int _growCnt = 0;
    Direction _movingDir = Direction::Up;
    std::list<Coord> _coords;

  public:
    Snake(size_t posX, size_t posY);

    Coord getHeadCoord() const;
    void setHeadCoord(Coord newHeadPos);

    void move(Direction direction);

    void grow();

    void draw(Board &board) const final;

  private:
    void updateDirection(Direction direction);
};
