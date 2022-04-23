#pragma once
#include <utility>

#include "Board.h"

class Food
{
  private:
    Coord _coords = {0, 0};

  public:
    Food() = default;
    Food(Coord coords);

    friend Board &operator<<(Board &board, const Food &food);
};
