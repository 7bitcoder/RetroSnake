#include "Food.h"

Food::Food(Coord coords) : _coords(coords) {}

void Food::draw(Board &board) const { board.setField(_coords, Board::Food); }

Board &operator<<(Board &board, const Food &food) { return board; }
