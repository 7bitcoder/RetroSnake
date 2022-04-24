#pragma once
#include "Board.h"

enum Key
{
    Up,
    Down,
    Left,
    Right,
    None
};

class OsApi
{
  private:
    OsApi();

  public:
    OsApi(OsApi const &) = delete;
    void operator=(OsApi const &) = delete;

    static OsApi &instance();

    Key getCurrentKeyPressed() const;

    void clearConsole();
};
