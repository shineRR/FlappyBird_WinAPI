//
// Created by shine on 11/3/2020.
//

#include "Scene.h"
#include "gdiplus.h"
#include "GameState.h"

Scene::Scene() {}

Scene::Scene(GameState* _state, Bird* _bird, HWND* hWnd) {
    state = _state;
    bird = _bird;
}

void Scene::Render(HWND hWnd) {
//    HDC hdc1 = GetDC(hWnd);
//    char fpsText[255] = "FPS = ";
//    strcpy(fpsText, "60");
//    RECT rect = {0, 0, 100, 80};
//    DrawTextA(hdc1, fpsText, strlen(fpsText), &rect, DT_NOCLIP);
    std::string assetDir = GetAssetsDir();
    RECT windowRect;
    if(!GetClientRect(hWnd, &windowRect))
        GetLastError();
    InvalidateRect(hWnd, nullptr, FALSE);

    int left = windowRect.left;
    int top = windowRect.top;
    int width = windowRect.right - windowRect.left;
    int height = windowRect.bottom - windowRect.top;

    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hWnd, &ps);
    HDC memDC = CreateCompatibleDC(hdc);
    HBITMAP hBM = CreateCompatibleBitmap(hdc, width, height);
    HBITMAP  oldbmp = (HBITMAP)SelectObject(memDC, hBM);

    Gdiplus::Graphics graphics(memDC);
    if (state->GetState() == INTRO) {
        DrawBackground(memDC, windowRect);
        DrawFloor(memDC, windowRect);
        DrawStartMenu(memDC, windowRect);
    } else {
        DrawBackground(memDC, windowRect);
        DrawFloor(memDC, windowRect);
        bird->DrawBird(memDC);
        pipe.DrawPipes(memDC);
//        DrawStartMenu(memDC, windowRect);
    }

    BitBlt(hdc, left, top, width, height, memDC, left, top, SRCCOPY);
    SelectObject(memDC, oldbmp);
    DeleteObject(hBM);
    DeleteDC(memDC);

    EndPaint(hWnd, &ps);
}

void Scene::DrawStartMenu(HDC &memDC, RECT windowRect) {
    int width = windowRect.right - windowRect.left;
    int height = windowRect.bottom - windowRect.top;

    int menuWidth = width / 2;
    int menuHeight = height / 2;
    int menuX = (width - menuWidth) / 2;
    int menuY = (height - menuHeight) / 2;

    Gdiplus::Graphics graphics(memDC);
    Gdiplus::Rect destRect(menuX, menuY , menuWidth, menuHeight);
    Gdiplus::Image image(L"C:\\Users\\shine\\Desktop\\Dev\\FlappyBird_WinAPI\\Assets\\message.png");
    graphics.DrawImage(&image, destRect);
}

void Scene::DrawFloor(HDC &memDC, RECT windowRect) {
    int width = windowRect.right - windowRect.left;
    int height = windowRect.bottom - windowRect.top;

    Gdiplus::Graphics graphics(memDC);
    Gdiplus::Rect destRect(0, height * 0.87, width, height * 0.2);
    Gdiplus::Image image(L"C:\\Users\\shine\\Desktop\\Dev\\FlappyBird_WinAPI\\Assets\\base.png");
    graphics.DrawImage(&image, destRect);
}


void Scene::DrawBackground(HDC &memDC, RECT windowRect) {

    int width = windowRect.right - windowRect.left;
    int height = windowRect.bottom - windowRect.top;

    Gdiplus::Graphics graphics(memDC);
    Gdiplus::Rect destRect(0, 0, width, height);
    Gdiplus::Image image(L"C:\\Users\\shine\\Desktop\\Dev\\FlappyBird_WinAPI\\Assets\\background-night.png");
    graphics.DrawImage(&image, destRect);
}

std::string Scene::GetAssetsDir() {
    char buff[FILENAME_MAX]; //create string buffer to hold path
    GetCurrentDir(buff, FILENAME_MAX );
    std::string currDir(buff);
    std::size_t pos = currDir.find_last_of('\\');      // position of "live" in str
    std::string assetDir = currDir.substr(0, pos).append("\\Assets\\");     // get from "live" to the end
    return assetDir;
}

void Scene::MovePipe() {
    if (!isActive) return;
    pipe.Movement();
}

void Scene::UpdateObjectPositions(RECT windowRect) {
    bird->UpdateBirdPosition(windowRect);
    pipe.updatePipesPosition(windowRect, 0, false);
}

