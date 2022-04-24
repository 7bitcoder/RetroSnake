#include <chrono>
#include <iostream>
#include <sstream>
#include <thread>
#include <time.h>

#include "Board.h"
#include "Game.h"
#include "OsApi.h"

using namespace std::chrono_literals;

namespace
{
    Direction keyToDirection(Key key)
    {
        if (key == Key::Up)
        {
            return Direction::Up;
        }
        if (key == Key::Down)
        {
            return Direction::Down;
        }
        if (key == Key::Right)
        {
            return Direction::Right;
        }
        if (key == Key::Left)
        {
            return Direction::Left;
        }
        return Direction::Up;
    }
} // namespace

Game::Game(size_t width, size_t height) : _board(width, height), _snake(width / 2, height / 2)
{
    srand(time(NULL));
    _board.draw(_snake);
    spawnNewFood();
    _board.draw(_food);
}

void Game::run()
{
    Direction currentDirection = Direction::Up;

    auto oneFrameTimeMs = std::chrono::milliseconds{int(1000.0 / _gameSpeed)};
    auto lastFrameTime = std::chrono::high_resolution_clock::now();
    while (_state == State::Ok)
    {
        std::this_thread::sleep_for(200us);
        if (auto keyPressed = OsApi::instance().getCurrentKeyPressed(); keyPressed != Key::None)
        {
            currentDirection = keyToDirection(keyPressed);
        }

        if (std::chrono::high_resolution_clock::now() - lastFrameTime > oneFrameTimeMs)
        {
            lastFrameTime = std::chrono::high_resolution_clock::now();
            update(currentDirection);
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

void Game::update(Direction direction)
{
    _snake.move(direction);

    auto headCoord = _snake.getHeadCoord();
    auto targetField = _board.getField(headCoord);
    if (targetField == Board::Border)
    {
        headCoord = _board.normalize(headCoord);
        _snake.setHeadCoord(headCoord);
        targetField = _board.getField(headCoord);
    }
    if (targetField == Board::Snake)
    {
        _state = State::Over;
        return;
    }

    _board.clear();
    _board.draw(_snake);

    if (targetField == Board::Food)
    {
        _points++;
        _snake.grow();
        spawnNewFood();
    }
    _board.draw(_food);
}

void Game::print() const
{
    OsApi::instance().clearConsole();

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
