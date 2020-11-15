//
// Created by shine on 11/3/2020.
//

#include <vector>
#include "Scene.h"
#include "gdiplus.h"
#include "GameState.h"

Scene::Scene() {}

Scene::Scene(GameState* _state, Bird* _bird) {
    state = _state;
    bird = _bird;
}

void Scene::Render(HWND hWnd) {
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
    switch (state->GetState()) {
        case INTRO: {
            DrawBackground(memDC, windowRect);
            DrawFloor(memDC, windowRect);
            DrawStartMenu(memDC, windowRect);
            pipe.DrawCollectedCoins(graphics, coins);
            break;
        }
        case GAMELEVEL: {
            DrawBackground(memDC, windowRect);
            DrawFloor(memDC, windowRect);
            if (pipe.DrawPipes(memDC, bird->GetPos())) {
                state->ChangeToScore();
                isActive = false;
            }
            bird->DrawBird(memDC);
//        DrawStartMenu(memDC, windowRect);
            break;
        }
        case SCORE: {
            DrawBackground(memDC, windowRect);
            DrawFloor(memDC, windowRect);
            DrawGameOver(memDC, windowRect);
            std::string text("Traveled Distance: ");
            text += std::to_string(pipe.GetTraveledDistance());
            Gdiplus::RectF rectF(15.0f, 10.0f, 100.0f, 100.0f);
            pipe.DrawTextZ(graphics, text, rectF);
            DrawScore(memDC, windowRect);

            break;
        }
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

void Scene::DrawScore(HDC &memDC, RECT windowRect) {
    int score = pipe.GetTraveledDistance();
    std::vector<int> vector;
    while (score != 0) {
        int part = score % 10;
        score /= 10;
        vector.push_back(part);
    }
    for (int i = 0; i < vector.size(); ++i) {
        std::cout << vector[i] << std::endl;
    }
    std::cout << "_____________________" << std::endl;
}

void Scene::DrawGameOver(HDC &memDC, RECT windowRect) {
    int width = windowRect.right - windowRect.left;
    int height = windowRect.bottom - windowRect.top;

    int menuWidth = width / 4;
    int menuHeight = height / 4;
    int menuX = (width - menuWidth) / 2;
    int menuY = (height - menuHeight) / 8;

    Gdiplus::Graphics graphics(memDC);
    Gdiplus::Rect destRect(menuX, menuY , menuWidth, menuHeight);
    Gdiplus::Image image(L"C:\\Users\\shine\\Desktop\\Dev\\FlappyBird_WinAPI\\Assets\\gameover.png");
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

void Scene::MovePipe(RECT windowRect) {
    if (!isActive) return;
    pipe.ValidateMap(windowRect);
    pipe.Movement();
}

void Scene::UpdateObjectPositions(RECT windowRect) {
    bird->UpdateBirdPosition(windowRect);
    pipe.updatePipesPosition(windowRect, pipe.pipes, 0, false);
}

int Scene::ResetCounter() {
    coins = pipe.ResetCounter();
    pipe.StopCounting();
}
