#include "TouchpadManager.h"
#include "TouchProcessor.h"
#include "CoordinateMapper.h"
#include "Containers.h"
#include <cstring>
#include <iostream>
#include <iomanip>
#include <string>
#include <regex>
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#define VERSION_NAME "1.2.0"
#define AUTHOR "crossbowffs"
#define PROJECT_URL "https://github.com/apsun/AbsoluteTouch"

TouchpadManager *g_touchpadManager = nullptr;
TouchProcessor g_touchProcessor;
CoordinateMapper g_coordinateMapper;
bool g_touchpadEnabledModified = false;
bool g_debugMode = false;

void PrintUsage()
{
    std::cerr << "usage: AbsoluteTouch.exe [-w <width>] [-h <height>] [-t]" << std::endl;
    std::cerr << "  -t x1,y1,x2,y2  Sets the mapped touchpad region" << std::endl;
    std::cerr << "  -s x1,y1,x2,y2  Sets the mapped screen region" << std::endl;
    std::cerr << "  -m              Enables the touchpad on start, disables it on exit" << std::endl;
    std::cerr << "  -w weight       Sets the touch smoothing weight factor (0 to 1, default 0)" << std::endl;
    std::cerr << "  -d              Enables debug mode (may reduce performance)" << std::endl;
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

void OnTouch(TouchEvent e)
{
    if (!e.touching) {
        g_touchProcessor.TouchEnded();
    } else {
        Point<long> averagedPt = g_touchProcessor.Update(e.point);
        Point<int> screenPt = g_coordinateMapper.TouchpadToScreenCoords(averagedPt);
        SetCursorPos(screenPt.x, screenPt.y);
        if (g_debugMode) {
            std::cout << "Touch event:" << std::endl;
            std::cout << "  Raw touch point: " << e.point << std::endl;
            std::cout << "  Averaged touch point: " << averagedPt << std::endl;
            std::cout << "  Target screen point: " << screenPt << std::endl;
        }
    }
}

template <typename T>
bool ParseRect(const std::string &str, Rect<T> *out)
{
    std::regex re("(\\d+),(\\d+),(\\d+),(\\d+)");
    std::smatch match;
    if (!std::regex_match(str, match, re))
        return false;
    T x1 = std::stoi(match[1].str());
    T y1 = std::stoi(match[2].str());
    T x2 = std::stoi(match[3].str());
    T y2 = std::stoi(match[4].str());
    if (x1 > x2)
        return false;
    if (y1 > y2)
        return false;
    out->x1 = x1;
    out->y1 = y1;
    out->x2 = x2;
    out->y2 = y2;
    return true;
}

int main(int argc, char *argv[])
{
    // Parse command-line args
    bool setScreenRect = false;
    bool setTouchpadRect = false;
    Rect<int> screenRect;
    Rect<long> touchpadRect;
    bool manageTouchpad = false;
    float smoothingWeight = 0.0f;
    for (int i = 1; i < argc; ++i) {
        bool valid = true;
        if (std::strcmp(argv[i], "-t") == 0 && i < argc - 1) {
            if (!ParseRect(argv[++i], &touchpadRect))
                valid = false;
            setTouchpadRect = true;
        } else if (std::strcmp(argv[i], "-s") == 0 && i < argc - 1) {
            if (!ParseRect(argv[++i], &screenRect))
                valid = false;
            setScreenRect = true;
        } else if (std::strcmp(argv[i], "-m") == 0) {
            manageTouchpad = true;
        } else if (std::strcmp(argv[i], "-d") == 0) {
            g_debugMode = true;
        } else if (std::strcmp(argv[i], "-w") == 0 && i < argc - 1) {
            smoothingWeight = (float)std::stod(argv[++i]);
            if (smoothingWeight < 0.0f || smoothingWeight > 1.0f)
                valid = false;
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

    // Set touch smoothing weight
    g_touchProcessor.SetWeight(smoothingWeight);
    std::cout << "Touch smoothing weight factor: " << smoothingWeight << std::endl;

    // Get touchpad dimensions
    if (!setTouchpadRect) {
        touchpadRect = g_touchpadManager->GetDefaultTouchpadRect();
    }
    std::cout << "Touchpad area: " << touchpadRect << std::endl;
    g_coordinateMapper.SetTouchpadRect(touchpadRect);

    // Get screen dimensions
    if (!setScreenRect) {
        screenRect.x1 = 0;
        screenRect.y1 = 0;
        screenRect.x2 = GetSystemMetrics(SM_CXSCREEN) - 1;
        screenRect.y2 = GetSystemMetrics(SM_CYSCREEN) - 1;
    }
    std::cout << "Screen area: " << screenRect << std::endl;
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
    if (manageTouchpad && !g_touchpadManager->IsTouchpadEnabled()) {
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
