#pragma once

class Board;

struct IDrawable
{
    virtual void draw(Board &board) const = 0;

    virtual ~IDrawable() = default;
};