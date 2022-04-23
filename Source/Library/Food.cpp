#include "Food.h"

Food::Food(Coord coords) : _coords(coords) {}

Board &operator<<(Board &board, const Food &food)
{
    board.setField(food._coords, Board::Food);
    return board;
}
