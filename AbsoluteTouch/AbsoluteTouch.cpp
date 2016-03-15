#include "TouchpadManager.h"
#include "CoordinateMapper.h"
#include "Containers.h"
#include <cstdlib>
#include <cerrno>
#include <cstring>
#include <iostream>
#include <iomanip>
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#define VERSION_NAME "1.1.0-dev"
#define AUTHOR "crossbowffs"
#define PROJECT_URL "https://github.com/apsun/AbsoluteTouch"

TouchpadManager *g_touchpadManager = nullptr;
CoordinateMapper g_coordinateMapper;
bool g_touchpadEnabledModified = false;
bool g_debugMode = false;

void PrintUsage()
{
    std::cerr << "usage: AbsoluteTouch.exe [-w <width>] [-h <height>] [-t]" << std::endl;
    std::cerr << "  -w <width>   Sets the width of the mapped screen region." << std::endl;
    std::cerr << "  -h <height>  Sets the height of the mapped screen region." << std::endl;
    std::cerr << "  -t           Enables the touchpad on start, disables it on exit" << std::endl;
}

void CleanUp()
{
    std::cout << "--------------------------------------------------" << std::endl;
    std::cout << "Exiting..." << std::endl;
    if (g_touchpadManager != nullptr) {
        if (g_touchpadEnabledModified) {
            g_touchpadManager->SetTouchpadEnabled(false);
            std::cout << "Disabled touchpad" << std::endl;
        }

        g_touchpadManager->SetTouchCallback(nullptr);
        std::cout << "Unregistered touch callback" << std::endl;

        g_touchpadManager->Unacquire();
        std::cout << "Released exclusive touchpad access" << std::endl;

        delete g_touchpadManager;
    }
}

BOOL WINAPI OnConsoleSignal(DWORD signal)
{
    if (signal == CTRL_C_EVENT || signal == CTRL_CLOSE_EVENT)
        CleanUp();
    return FALSE;
}

void OnTouch(long touchpadX, long touchpadY)
{
    if (g_debugMode) {
        std::cout << "Touchpad position: (" << touchpadX << ", " << touchpadY << ")";
        std::cout << std::setw(80) << "\r" << std::flush;
    }
    Point<int> screenPt = g_coordinateMapper.TouchpadToScreenCoords(touchpadX, touchpadY);
    SetCursorPos(screenPt.x, screenPt.y);
}

int main(int argc, char *argv[])
{
    // Parse command-line args
    int forceWidth = 0;
    int forceHeight = 0;
    bool manageTouchpad = false;
    for (int i = 1; i < argc; ++i) {
        bool valid = true;
        if (std::strcmp(argv[i], "-w") == 0 && i < argc - 1) {
            forceWidth = std::strtol(argv[++i], nullptr, 10);
            if (forceWidth <= 0 || errno == ERANGE) valid = false;
        } else if (std::strcmp(argv[i], "-h") == 0  && i < argc - 1) {
            forceHeight = std::strtol(argv[++i], nullptr, 10);
            if (forceHeight <= 0 || errno == ERANGE) valid = false;
        } else if (std::strcmp(argv[i], "-t") == 0) {
            manageTouchpad = true;
        } else if (std::strcmp(argv[i], "-d") == 0) {
            g_debugMode = true;
        } else {
            valid = false;
        }
        if (!valid) {
            PrintUsage();
            return 1;
        }
    }

    // Print init info
    std::cout << "AbsoluteTouch v" << VERSION_NAME << std::endl;
    std::cout << "Author: " << AUTHOR << std::endl;
    std::cout << "Project page: " << PROJECT_URL << std::endl;
    std::cout << "--------------------------------------------------" << std::endl;
    std::cout << "Starting..." << std::endl;

    // Heap-alloc to allow custom lifecycle management
    g_touchpadManager = new TouchpadManager;

    // Initialize touchpad manager
    if (!g_touchpadManager->Initialize()) {
        std::cerr << "Error: could not initialize touchpad manager" << std::endl;
        CleanUp();
        return 1;
    }
    std::cout << "Initialized touchpad manager" << std::endl;

    // Get touchpad dimensions
    Rect<long> touchpadRect = g_touchpadManager->GetDefaultTouchpadRect();
    std::cout << "Touchpad area: " << touchpadRect << std::endl;

    // Get screen dimensions
    int screenWidth = forceWidth > 0 ? forceWidth : GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = forceHeight > 0 ? forceHeight : GetSystemMetrics(SM_CYSCREEN);
    Rect<int> screenRect(0, 0, screenWidth, screenHeight);
    std::cout << "Screen area: " << screenRect << std::endl;

    g_coordinateMapper.SetTouchpadRect(touchpadRect);
    g_coordinateMapper.SetScreenRect(screenRect);

    // Acquire exclusive touchpad access
    if (!g_touchpadManager->Acquire()) {
        std::cerr << "Error: could not acquire exclusive touchpad access" << std::endl;
        CleanUp();
        return 1;
    }
    std::cout << "Acquired exclusive touchpad access" << std::endl;

    // Register touchpad touch callback
    g_touchpadManager->SetTouchCallback(OnTouch);
    std::cout << "Registered touch listener" << std::endl;

    // Enable touchpad if -t flag was specified
    if (manageTouchpad) {
        g_touchpadManager->SetTouchpadEnabled(true);
        g_touchpadEnabledModified = true;
        std::cout << "Enabled touchpad" << std::endl;
    }

    // Set cleanup handler
    if (!SetConsoleCtrlHandler(OnConsoleSignal, TRUE)) {
        std::cerr << "Error: failed to register console control handler" << std::endl;
        CleanUp();
        return 1;
    }
    std::cout << "Registered console control handler" << std::endl;

    // Print usage instructions
    std::cout << "--------------------------------------------------" << std::endl;
    std::cout << "Initialization complete, absolute touch mode enabled!" << std::endl;
    std::cout << "Keep this window open until you wish to exit absolute touch mode." << std::endl;
    std::cout << "To exit the program, you can use CTRL-C." << std::endl;

    // Main message loop
    MSG msg;
    BOOL ret;
    while ((ret = GetMessage(&msg, nullptr, 0, 0)) != 0) {
        if (ret == -1) {
            break;
        } else {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    CleanUp();
    return 0;
}
