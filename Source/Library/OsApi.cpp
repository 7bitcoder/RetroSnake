#include "OsApi.h"

#ifdef _WIN32
#include <stdio.h>
#include <tchar.h>
#include <windows.h>
#include <winuser.h>

#define WINDOWS
#endif

#ifdef linux

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define LINUX
#endif

namespace
{
#ifdef WINDOWS
    Key getCurrentKeyPressedOs()
    {
        if ((1 << 15) & GetAsyncKeyState(VK_UP))
        {
            return Key::Up;
        }
        if ((1 << 15) & GetAsyncKeyState(VK_DOWN))
        {
            return Key::Down;
        }
        if ((1 << 15) & GetAsyncKeyState(VK_LEFT))
        {
            return Key::Left;
        }
        if ((1 << 15) & GetAsyncKeyState(VK_RIGHT))
        {
            return Key::Right;
        }
        return Key::None;
    }

    void clearConsoleOs()
    {
        HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleCursorPosition(hOut, {.X = 0, .Y = 0});
    }
#endif

#ifdef LINUX
    Key getCurrentKeyPressedOs()
    {
        if ((1 << 15) & GetAsyncKeyState(VK_UP))
        {
            return Key::Up;
        }
        if ((1 << 15) & GetAsyncKeyState(VK_DOWN))
        {
            return Key::Down;
        }
        if ((1 << 15) & GetAsyncKeyState(VK_LEFT))
        {
            return Key::Left;
        }
        if ((1 << 15) & GetAsyncKeyState(VK_RIGHT))
        {
            return Key::Right;
        }
        return Key::None;
    }

    void clearConsoleOs()
    {
        HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleCursorPosition(hOut, {.X = 0, .Y = 0});
    }
#endif

} // namespace

OsApi &OsApi::instance()
{
    static OsApi instance;
    return instance;
}

Key OsApi::getCurrentKeyPressed() const { return getCurrentKeyPressedOs(); }

void OsApi::clearConsole() { clearConsoleOs(); }
