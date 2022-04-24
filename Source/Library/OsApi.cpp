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
    void initOs() {}

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
    void initOs() {

    }

    Key getCurrentKeyPressedOs()
    {
        int ch = getchar(); 
        // if (ch == KEY_UP)  
        // {
        //     return Key::Up;
        // }
        // if (ch == KEY_DOWN)  
        // {
        //     return Key::Down;
        // }
        // if (ch == KEY_LEFT)  
        // {
        //     return Key::Left;
        // }
        // if (ch == KEY_RIGHT)  
        // {
        //     return Key::Right;
        // }
        return Key::None;
    }

    void clearConsoleOs()
    {
        printf("\033[2J\033[1;1H");
    }
#endif

} // namespace

OsApi::OsApi() { initOs(); }

OsApi &OsApi::instance()
{
    static OsApi instance;
    return instance;
}

Key OsApi::getCurrentKeyPressed() const { return getCurrentKeyPressedOs(); }

void OsApi::clearConsole() { clearConsoleOs(); }
