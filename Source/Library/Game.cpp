#include <chrono>
#include <iostream>
#include <sstream>
#include <thread>
#include <time.h>
#include <windows.h>
#include <winuser.h>

#include "Game.h"

using namespace std::chrono_literals;

namespace
{
    const double FRAMERATE = 5.0;

    Coord moveCoord(Direction direction, Coord coord)
    {
        switch (direction)
        {
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

Game::Game(size_t width, size_t height) : _board(width, height), _snake(width / 2, height / 2)
{
    srand(time(NULL));
    _board << _snake;
    spawnNewFood();
    _board << _food;
}

void Game::run()
{
    auto oneFrameTimeMs = std::chrono::milliseconds{int(1000.0 / FRAMERATE)};
    auto lastFrameTime = std::chrono::high_resolution_clock::now();
    while (_state == State::Ok)
    {
        std::this_thread::sleep_for(200us);
        checkDirection();

        if (std::chrono::high_resolution_clock::now() - lastFrameTime > oneFrameTimeMs)
        {
            lastFrameTime = std::chrono::high_resolution_clock::now();
            update();
            print();
        }
    }
    if (_state == State::Over)
    {
        std::cout << "You lost with " << _points << " points";
    }
    if (_state == State::Won)
    {
        std::cout << "You won with " << _points << " points";
    }
}

void Game::update()
{
    auto newHeadPos = moveCoord(_direction, _snake.getHeadCoord());

    auto targetField = _board.getField(newHeadPos);
    if (targetField == Board::Snake)
    {
        _state = State::Over;
        return;
    }
    if (targetField == Board::Border)
    {
        newHeadPos = _board.normalize(newHeadPos);
    }

    auto eat = targetField == Board::Food;
    _snake.move(newHeadPos, _direction, eat);

    _board.clear();
    _board << _snake;

    if (eat)
    {
        _points++;
        spawnNewFood();
    }
    _board << _food;
}

void Game::checkDirection()
{
    if ((1 << 15) & GetAsyncKeyState(VK_UP) && _snake.getDirection() != Direction::Down)
    {
        _direction = Direction::Up;
    }
    else if ((1 << 15) & GetAsyncKeyState(VK_DOWN) && _snake.getDirection() != Direction::Up)
    {
        _direction = Direction::Down;
    }
    else if ((1 << 15) & GetAsyncKeyState(VK_LEFT) && _snake.getDirection() != Direction::Right)
    {
        _direction = Direction::Left;
    }
    else if ((1 << 15) & GetAsyncKeyState(VK_RIGHT) && _snake.getDirection() != Direction::Left)
    {
        _direction = Direction::Right;
    }
}

void Game::print() const
{
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hOut, {.X = 0, .Y = 0});

    std::cout << "Points: " << _points << std::endl << _board;
}

void Game::spawnNewFood()
{
    auto freeSpace = _board.getEmptyCoords();

    if (freeSpace.empty())
    {
        _state = State::Won;
        return;
    }
    _food = Food{freeSpace.at(rand() % freeSpace.size())};
}
