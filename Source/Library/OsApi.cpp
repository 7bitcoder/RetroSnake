#include "OsApi.h"

#ifdef _WIN32
#include <stdio.h>
#include <tchar.h>
#include <windows.h>
#include <winuser.h>

#define WINDOWS
#endif

#ifdef linux

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

#define LINUX
#endif

namespace
{
#ifdef WINDOWS
    void initOs() {}

    Key getCurrentKeyPressedOs()
    {
        if ((1 << 15) & GetAsyncKeyState('W'))
        {
            return Key::Up;
        }
        if ((1 << 15) & GetAsyncKeyState('S'))
        {
            return Key::Down;
        }
        if ((1 << 15) & GetAsyncKeyState('A'))
        {
            return Key::Left;
        }
        if ((1 << 15) & GetAsyncKeyState('D'))
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
    void initOs() {}

    char getch()
    {
        char buf = 0;
        struct termios old = {0};
        if (tcgetattr(0, &old) < 0)
            perror("tcsetattr()");
        old.c_lflag &= ~ICANON;
        old.c_lflag &= ~ECHO;
        old.c_cc[VMIN] = 0;
        old.c_cc[VTIME] = 0;
        if (tcsetattr(0, TCSANOW, &old) < 0)
            perror("tcsetattr ICANON");
        if (read(0, &buf, 1) < 0)
            perror("read()");
        old.c_lflag |= ICANON;
        old.c_lflag |= ECHO;
        if (tcsetattr(0, TCSADRAIN, &old) < 0)
            perror("tcsetattr ~ICANON");

        return (buf);
    }

    Key getCurrentKeyPressedOs()
    {
        int ch = getch();
        if (ch == 'w')
        {
            return Key::Up;
        }
        if (ch == 's')
        {
            return Key::Down;
        }
        if (ch == 'a')
        {
            return Key::Left;
        }
        if (ch == 'd')
        {
            return Key::Right;
        }
        return Key::None;
    }

    void clearConsoleOs() { printf("\033[2J\033[1;1H"); }
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
