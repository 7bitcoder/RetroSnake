#pragma once
#include <string>
#include <vector>

#include "IDrawable.h"

using Coord = std::pair<size_t, size_t>;
enum class Direction
{
    Up,
    Down,
    Left,
    Right
};

class Board
{
  public:
    enum Field : char
    {
        Border = '#',
        Snake = '*',
        Food = 'O',
        Empty = ' '
    };
    using Matrix = std::vector<std::vector<Field>>;

  private:
    size_t _height = 0;
    size_t _width = 0;
    Matrix _board;

  public:
    Board(size_t width, size_t height);

    std::vector<Coord> getEmptyCoords() const;

    Field getField(Coord coords) const;
    void setField(Coord coords, Field value);

    void clear();

    Coord normalize(Coord coord);

    void draw(const IDrawable &drawable);

    friend std::ostream &operator<<(std::ostream &output, const Board &board);
};
