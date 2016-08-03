#include "CCoInitialize.h"
#include "Containers.h"
#include "CoordinateMapper.h"
#include "InputHelper.h"
#include "TouchProcessor.h"
#include "TouchpadManager.h"
#include <cstring>
#include <exception>
#include <iostream>
#include <iomanip>
#include <string>
#include <regex>
#include <Windows.h>

#define VERSION_NAME "1.4.0"
#define AUTHOR "crossbowffs"
#define PROJECT_URL "https://github.com/apsun/AbsoluteTouch"

class TouchCallbackImpl : public TouchCallback
{
public:
    void SetTouchpadRect(Rect<long> touchpadRect)
    {
        m_coordMapper.SetTouchpadRect(touchpadRect);
    }

    void SetScreenRect(Rect<long> screenRect)
    {
        m_coordMapper.SetScreenRect(screenRect);
    }

    void SetSmoothingWeight(int weight)
    {
        m_touchProcessor.SetWeight(weight);
    }

    void SetSendClick(bool sendClick)
    {
        m_sendClick = sendClick;
    }

private:
    void OnTouchStarted(Point<long> touchPt) override
    {
        if (m_sendClick) {
            SendLeftDown(TouchToScreen(touchPt));
        } else {
            MoveCursor(TouchToScreen(touchPt));
        }
    }

    void OnTouchMoved(Point<long> touchPt) override
    {
        MoveCursor(TouchToScreen(touchPt));
    }

    void OnTouchEnded() override
    {
        if (m_sendClick) {
            SendLeftUp();
        }
        m_touchProcessor.TouchEnded();
    }

    Point<long> TouchToScreen(Point<long> touchPt)
    {
        Point<long> avgPt = m_touchProcessor.Update(touchPt);
        Point<long> screenPt = m_coordMapper.TouchToScreenCoords(avgPt);
        return screenPt;
    }

    CoordinateMapper m_coordMapper;
    TouchProcessor m_touchProcessor;
    bool m_sendClick = false;
};

TouchpadManager *g_touchpadManager = nullptr;
TouchCallbackImpl *g_touchCallback = nullptr;
bool g_touchpadEnabledModified = false;

void PrintUsage()
{
    std::cerr << "usage: AbsoluteTouch.exe <args>\n";
    std::cerr << "  -t x1,y1,x2,y2  Set the mapped touchpad region\n";
    std::cerr << "  -s x1,y1,x2,y2  Set the mapped screen region\n";
    std::cerr << "  -w weight       Set the touch smoothing factor\n";
    std::cerr << "  -c              Enable tap to click\n";
    std::cerr << "  -m              Enable/disable the touchpad on start/exit\n";
    std::cerr << std::flush;
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
        g_touchpadManager = nullptr;
    }
    if (g_touchCallback != nullptr) {
        delete g_touchCallback;
        g_touchCallback = nullptr;
    }
}

BOOL WINAPI OnConsoleSignal(DWORD signal)
{
    switch (signal) {
    case CTRL_C_EVENT:
    case CTRL_BREAK_EVENT:
    case CTRL_CLOSE_EVENT:
        CleanUp();
        break;
    }
    return FALSE;
}

bool ParseRect(const std::string &str, Rect<int> *out)
{
    std::regex re("(\\d+),(\\d+),(\\d+),(\\d+)");
    std::smatch match;
    if (!std::regex_match(str, match, re))
        return false;
    int x1, y1, x2, y2;
    try {
        x1 = std::stoi(match[1].str());
        y1 = std::stoi(match[2].str());
        x2 = std::stoi(match[3].str());
        y2 = std::stoi(match[4].str());
    } catch (const std::invalid_argument &) {
        return false;
    } catch (const std::out_of_range &) {
        return false;
    }
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

bool ParsePercent(const std::string &str, int *out)
{
    int value;
    try {
        value = std::stoi(str);
    } catch (const std::invalid_argument &) {
        return false;
    } catch (const std::out_of_range &) {
        return false;
    }
    if (value < 0 || value > 100)
        return false;
    *out = value;
    return true;
}

Rect<long> RelativeToAbsoluteRect(Rect<long> base, Rect<int> scale)
{
    Rect<long> ret;
    ret.x1 = base.x1 + base.width() * scale.x1 / 100;
    ret.x2 = base.x1 + base.width() * scale.x2 / 100;
    ret.y1 = base.y1 + base.height() * scale.y1 / 100;
    ret.y2 = base.y1 + base.height() * scale.y2 / 100;
    return ret;
}

int main(int argc, char *argv[])
{
    // Parse command-line args
    Rect<int> screenRect(0, 0, 100, 100);
    Rect<int> touchpadRect(0, 0, 100, 100);
    bool manageTouchpad = false;
    bool sendClick = false;
    int smoothingWeight = 0;
    for (int i = 1; i < argc; ++i) {
        bool valid = true;
        if (std::strcmp(argv[i], "-t") == 0 && i < argc - 1) {
            if (!ParseRect(argv[++i], &touchpadRect))
                valid = false;
        } else if (std::strcmp(argv[i], "-s") == 0 && i < argc - 1) {
            if (!ParseRect(argv[++i], &screenRect))
                valid = false;
        } else if (std::strcmp(argv[i], "-w") == 0 && i < argc - 1) {
            if (!ParsePercent(argv[++i], &smoothingWeight))
                valid = false;
        } else if (std::strcmp(argv[i], "-m") == 0) {
            manageTouchpad = true;
        } else if (std::strcmp(argv[i], "-c") == 0) {
            sendClick = true;
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

    // Initialize COM
    CCoInitialize init;

    // Set cleanup handler
    if (!SetConsoleCtrlHandler(OnConsoleSignal, TRUE)) {
        std::cerr << "Error: failed to register console control handler" << std::endl;
        CleanUp();
        return 1;
    }
    std::cout << "Registered console control handler" << std::endl;

    // Heap-alloc to allow custom lifecycle management
    try {
        g_touchpadManager = new TouchpadManager();
    } catch (const TouchpadInitException &e) {
        std::cerr << "Error: could not initialize touchpad manager" << std::endl;
        std::cerr << e.what() << std::endl;
        CleanUp();
        return 1;
    }
    std::cout << "Initialized touchpad manager" << std::endl;

    // Acquire exclusive touchpad access
    if (!g_touchpadManager->Acquire()) {
        std::cerr << "Error: could not acquire exclusive touchpad access" << std::endl;
        CleanUp();
        return 1;
    }
    std::cout << "Acquired exclusive touchpad access" << std::endl;

    // Register touchpad touch callback
    Rect<long> screenRectAbs = RelativeToAbsoluteRect(Rect<long>(0, 0, 65535, 65535), screenRect);
    Rect<long> touchRectAbs = RelativeToAbsoluteRect(g_touchpadManager->GetTouchpadRect(), touchpadRect);
    g_touchCallback = new TouchCallbackImpl();
    g_touchCallback->SetScreenRect(screenRectAbs);
    g_touchCallback->SetTouchpadRect(touchRectAbs);
    g_touchCallback->SetSmoothingWeight(smoothingWeight);
    g_touchCallback->SetSendClick(sendClick);
    g_touchpadManager->SetTouchCallback(g_touchCallback);
    std::cout << "Registered touch listener" << std::endl;

    // Enable touchpad if option was specified
    if (manageTouchpad && !g_touchpadManager->IsTouchpadEnabled()) {
        g_touchpadManager->SetTouchpadEnabled(true);
        g_touchpadEnabledModified = true;
        std::cout << "Enabled touchpad" << std::endl;
    }

    // Print usage instructions
    std::cout << "--------------------------------------------------" << std::endl;
    std::cout << "Initialization complete, absolute touch mode enabled!" << std::endl;
    std::cout << "Keep this window open until you wish to exit absolute touch mode." << std::endl;
    std::cout << "To exit the program, you can use CTRL-C." << std::endl;

    // Main message loop
    MSG msg;
    BOOL ret;
    while ((ret = GetMessage(&msg, nullptr, 0, 0)) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    CleanUp();
    return 0;
}
