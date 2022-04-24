#include <sstream>

#include "Board.h"

Board::Board(size_t width, size_t height) : _width(width), _height(height)
{
    for (size_t i = 0; i < _width; ++i)
    {
        _board.emplace_back(std::vector<Field>(_height, Field::Empty));
    }

    for (size_t w = 0; w < _width; w++)
    {
        for (size_t h = 0; h < _height; h++)
        {
            if (w == 0 || h == 0 || w == _width - 1 || h == _height - 1)
            {
                _board[w][h] = Field::Border;
            }
        }
    }
}

Board::Field Board::getField(Coord coords) const { return _board[coords.first][coords.second]; }

std::vector<Coord> Board::getEmptyCoords() const
{
    std::vector<Coord> freeSpace;

    for (size_t h = 0; h < _height; h++)
    {
        for (size_t w = 0; w < _width; w++)
        {
            if (_board[w][h] == Field::Empty)
            {
                freeSpace.push_back({w, h});
            }
        }
    }
    return freeSpace;
}

void Board::setField(Coord coords, Field value) { _board[coords.first][coords.second] = value; }

void Board::clear()
{
    for (size_t w = 1; w < _width - 1; w++)
    {
        for (size_t h = 1; h < _height - 1; h++)
        {
            _board[w][h] = Field::Empty;
        }
    }
}

Coord Board::normalize(Coord coord)
{
    auto [x, y] = coord;
    if (x == 0)
    {
        x = _width - 2;
    }
    else if (x == _width - 1)
    {
        x = 1;
    }
    else if (y == 0)
    {
        y = _height - 2;
    }
    else if (y == _height - 1)
    {
        y = 1;
    }
    return {x, y};
}

void Board::draw(const IDrawable &drawable) { drawable.draw(*this); }

std::ostream &operator<<(std::ostream &output, const Board &board)
{
    std::stringstream out;
    auto width = board._width, height = board._height;
    auto &rawBoard = board._board;
    for (size_t w = 0; w < width; w++)
    {
        for (size_t h = 0; h < height; h++)
        {
            out << rawBoard[w][h] << Board::Empty;
        }
        out << std::endl;
    }

    return output << out.str();
}
