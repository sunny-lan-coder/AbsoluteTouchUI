#include "TouchpadManager.h"
#include "Containers.h"
#include <cstdlib>
#include <cstring>
#include <iostream>
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#define VERSION_NAME "1.0.1"
#define AUTHOR "crossbowffs"
#define PROJECT_URL "https://github.com/apsun/AbsoluteTouch"

TouchpadManager *g_touchpadManager = NULL;
bool g_touchpadEnabledModified = false;

void usage()
{
    std::cerr << "usage: AbsoluteTouch.exe [-w <width>] [-h <height>] [-t]" << std::endl;
    std::cerr << "  -w <width>   Sets the width of the mapped screen region." << std::endl;
    std::cerr << "  -h <height>  Sets the height of the mapped screen region." << std::endl;
    std::cerr << "  -t           Enables the touchpad on start, disables it on exit" << std::endl;
}

void cleanup()
{
    std::cout << "--------------------------------------------------" << std::endl;
    std::cout << "Exiting..." << std::endl;
    if (g_touchpadManager) {
        if (g_touchpadEnabledModified) {
            g_touchpadManager->SetTouchpadEnabled(false);
            std::cout << "Disabled touchpad" << std::endl;
        }
        if (g_touchpadManager->Unacquire()) {
            std::cout << "Released exclusive touchpad access" << std::endl;
        }
        delete g_touchpadManager;
    }
}

BOOL WINAPI onexit(DWORD signal)
{
    if (signal == CTRL_C_EVENT || signal == CTRL_CLOSE_EVENT)
        cleanup();
    return FALSE;
}

int main(int argc, char *argv[])
{
    // Parse command-line args
    int forceWidth = 0;
    int forceHeight = 0;
    bool manageTouchpad = false;
    for (int i = 1; i < argc; ++i) {
        if (std::strcmp(argv[i], "-w") == 0 && i < argc - 1) {
            forceWidth = std::atoi(argv[++i]);
        } else if (std::strcmp(argv[i], "-h") == 0  && i < argc - 1) {
            forceHeight = std::atoi(argv[++i]);
        } else if (std::strcmp(argv[i], "-t") == 0 ) {
            manageTouchpad = true;
        } else {
            usage();
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

    // Get screen dimensions
    int screenWidth = forceWidth > 0 ? forceWidth : GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = forceHeight > 0 ? forceHeight : GetSystemMetrics(SM_CYSCREEN);
    Rect<int> screenRect(0, 0, screenWidth, screenHeight);

    // Initialize touchpad manager
    if (!g_touchpadManager->Initialize(screenRect)) {
        std::cerr << "Error: could not initialize touchpad manager" << std::endl;
        cleanup();
        return 1;
    }
    std::cout << "Initialized touchpad manager" << std::endl;

    // Acquire exclusive touchpad access
    if (!g_touchpadManager->Acquire()) {
        std::cerr << "Error: could not acquire exclusive touchpad access" << std::endl;
        cleanup();
        return 1;
    }
    std::cout << "Acquired exclusive touchpad access" << std::endl;

    // Enable touchpad if -t flag was specified
    if (manageTouchpad) {
        g_touchpadManager->SetTouchpadEnabled(true);
        g_touchpadEnabledModified = true;
        std::cout << "Enabled touchpad" << std::endl;
    }

    // Set cleanup handler
    if (!SetConsoleCtrlHandler(onexit, TRUE)) {
        std::cerr << "Error: failed to register console control handler" << std::endl;
        cleanup();
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
    while ((ret = GetMessage(&msg, NULL, 0, 0)) != 0) {
        if (ret == -1) {
            break;
        } else {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    cleanup();
    return 0;
}
