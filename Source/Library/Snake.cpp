#include "Snake.h"

Snake::Snake(size_t posX, size_t posY)
{
    _coords.push_back({posX, posY});     // head
    _coords.push_back({posX + 1, posY}); // tail
}

Coord Snake::getHeadCoord() const { return _coords.front(); }

void Snake::move(Coord newHeadPos, Direction dir, bool grow)
{
    _movingDir = dir;
    _coords.push_front(newHeadPos);
    if (!grow)
    {
        _coords.pop_back();
    }
}

Direction Snake::getDirection() const { return _movingDir; }

Board &operator<<(Board &board, const Snake &snake)
{
    for (auto coords : snake._coords)
    {
        board.setField(coords, Board::Snake);
    }
    return board;
}
