#pragma once
#include <utility>

#include "Board.h"
#include "IDrawable.h"

class Food : public IDrawable
{
  private:
    Coord _coords = {0, 0};

  public:
    Food() = default;
    Food(Coord coords);

    void draw(Board &board) const final;

    friend Board &operator<<(Board &board, const Food &food);
};
