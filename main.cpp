#include <iostream>
#include "windows.h"
#include "gdiplus.h"
#include "Game/Game.h"

#define TIMER_SECOND 1
#define BIRD_TIMER 2

const SIZE MIN_WINDOW_SIZE = {640,480};
const double FPS = 1000 / 60;
Game game = Game();

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    RECT windowRect;
    GetClientRect(hWnd, &windowRect);
    switch (message) {
        case WM_CREATE: {
            game.hWnd = hWnd;
            SetTimer(hWnd, TIMER_SECOND, FPS, NULL);
            SetTimer(hWnd, BIRD_TIMER, 400, NULL);
            break;
        }
        case WM_SIZE: {
            double width = (windowRect.right - windowRect.left);
            double height = (windowRect.bottom - windowRect.top);
            game.bird.UpdateMoveDistance(width, height);
            game.scene.UpdatePipePosition(windowRect);
            game.scene.Render(hWnd);
            break;
        }
        case WM_TIMER: {
            switch (wParam) {
                case TIMER_SECOND: {
                    game.scene.MovePipe();
                    game.scene.Render(hWnd);
                    break;
                }
                case BIRD_TIMER: {
                    game.bird.MoveVertical(windowRect, 1);
                    break;
                }
            }
            break;
        }
        case WM_GETMINMAXINFO: {
            LPMINMAXINFO lpMMI = (LPMINMAXINFO) lParam;
            lpMMI->ptMinTrackSize.x = MIN_WINDOW_SIZE.cx;
            lpMMI->ptMinTrackSize.y = MIN_WINDOW_SIZE.cy;
            double width = (windowRect.right - windowRect.left);
            double height = (windowRect.bottom - windowRect.top);
            game.bird.UpdateMoveDistance(width, height);
            game.scene.UpdatePipePosition(windowRect);
            game.scene.Render(hWnd);
            break;
        }
        case WM_KEYDOWN: {
            game.KeyAnalyse(hWnd, wParam, windowRect);
            break;
        }
        case WM_PAINT: {
           // game.Run(hWnd, wParam);
            break;
        }
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
    Gdiplus::GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR gdiplusToken;
    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, nullptr);
    WNDCLASSEX wcex; HWND hWnd; MSG msg;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = nullptr;
    wcex.lpszClassName = "Main";
    wcex.hIconSm = wcex.hIcon;
    RegisterClassEx(&wcex);
    hWnd = CreateWindow("Main", "Flappy Bird;",
                        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT,
                        CW_USEDEFAULT, 800, 600, nullptr, nullptr, hInstance, nullptr);
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);
    game.Run(hWnd);
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    Gdiplus::GdiplusShutdown(gdiplusToken);
    return (int)msg.wParam;
}
