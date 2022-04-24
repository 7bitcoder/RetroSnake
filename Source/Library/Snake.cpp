#include "Snake.h"
#include "Board.h"

namespace
{
    Coord moveCoord(Direction direction, Coord coord)
    {
        switch (direction)
        {
        default:
        case Direction::Up:
            coord.first--;
            break;
        case Direction::Down:
            coord.first++;
            break;
        case Direction::Left:
            coord.second--;
            break;
        case Direction::Right:
            coord.second++;
            break;
        }
        return coord;
    }
} // namespace

Snake::Snake(size_t posX, size_t posY)
{
    _coords.push_back({posX, posY});     // head
    _coords.push_back({posX + 1, posY}); // tail
}

Coord Snake::getHeadCoord() const { return _coords.front(); }

void Snake::move(Direction direction)
{
    updateDirection(direction);
    auto newCoord = moveCoord(_movingDir, getHeadCoord());
    _coords.push_front(newCoord);
    if (_growCnt > 0)
    {
        _growCnt--;
    }
    else
    {
        _coords.pop_back();
    }
}

void Snake::setHeadCoord(Coord newHeadPos) { _coords.front() = newHeadPos; }

void Snake::grow() { _growCnt++; }

void Snake::updateDirection(Direction direction)
{
    if (direction == Direction::Up && _movingDir != Direction::Down)
    {
        _movingDir = Direction::Up;
    }
    else if (direction == Direction::Down && _movingDir != Direction::Up)
    {
        _movingDir = Direction::Down;
    }
    else if (direction == Direction::Left && _movingDir != Direction::Right)
    {
        _movingDir = Direction::Left;
    }
    else if (direction == Direction::Right && _movingDir != Direction::Left)
    {
        _movingDir = Direction::Right;
    };
}

void Snake::draw(Board &board) const
{
    for (auto coords : _coords)
    {
        board.setField(coords, Board::Snake);
    }
}
