//
// Created by shine on 11/3/2020.
//

#include <vector>
#include "Scene.h"
#include "gdiplus.h"

Scene::Scene() {}

Scene::Scene(GameState* _state, Bird* _bird) {
    state = _state;
    bird = _bird;
    WCHAR * wcharBackground = Helper::GetWCHAR(Helper::GetAssetsDir());
    wcscat(wcharBackground, backgroundType);
    wcscpy(backgroundType, wcharBackground);
    shop = Shop(_bird, &pipe);
}

void Scene::Render(HWND hWnd) {
    std::string assetDir = Helper::GetAssetsDir();
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
    auto  oldbmp = (HBITMAP)SelectObject(memDC, hBM);

    Gdiplus::Graphics graphics(memDC);
    switch (state->GetState()) {
        case INTRO: {
            DrawBackground(memDC, windowRect);
            DrawFloor(memDC, windowRect);
            DrawStartMenu(memDC, windowRect);
            Pipe::DrawCollectedCoins(graphics,"Total Coins: ", coins);
            break;
        }
        case GAMELEVEL: {
            DrawBackground(memDC, windowRect);
            DrawFloor(memDC, windowRect);
            if (pipe.DrawPipes(memDC, bird->GetPos())) {
                coins += pipe.ResetCounter();
                state->ChangeToScore();
                isActive = false;
            }
            bird->DrawBird(memDC);
            break;
        }
        case SCORE: {
            DrawBackground(memDC, windowRect);
            DrawFloor(memDC, windowRect);
            DrawGameOver(memDC, windowRect);
            Pipe::DrawCollectedCoins(graphics, "Total Coins: ", coins);
            pipe.DrawTraveledDistance(graphics);
            DrawScore(memDC, windowRect);
            break;
        }
        case SHOP: {
            DrawBackground(memDC, windowRect);
            DrawFloor(memDC, windowRect);
            Pipe::DrawCollectedCoins(graphics,"Total Coins: ", coins);
            shop.DrawShop(memDC, windowRect);
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
    double width = windowRect.right - windowRect.left;
    double height = windowRect.bottom - windowRect.top;
    double coefX = width / DEFAULT_WINDOW_WIDTH;
    double coefY = height / DEFAULT_WINDOW_HEIGHT;

    int scoreWidth = int(width / 24 * coefX);
    int scoreHeight = int(height / 16 * coefY);
    int scoreX = int((width - scoreWidth) / 2);
    int scoreY = int((height - scoreHeight) / 2);

    Gdiplus::Graphics graphics(memDC);
    std::string assets = Helper::GetAssetsDir();

    std::vector<int> vector;
    do {
        int part = score % 10;
        score /= 10;
        vector.push_back(part);
    } while (score != 0);

    for (int i = vector.size(); i > 0; i--) {
        Gdiplus::Rect destRect(scoreX, scoreY, scoreWidth, scoreHeight);
        std::string imageName(assets);
        imageName += std::to_string(vector[i - 1]) + ".png";
        std::wstring wide_string = std::wstring(imageName.begin(), imageName.end());
        const wchar_t* result = wide_string.c_str();
        WCHAR wchar[255];
        wcscpy(wchar, result);
        Gdiplus::Image image(wchar);
        graphics.DrawImage(&image, destRect);
        scoreX += int(50 * coefX);
    }
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
    WCHAR * imageName = new WCHAR[255];
    wcscpy(imageName, L"C:\\Users\\shine\\Desktop\\Dev\\FlappyBird_WinAPI\\Assets\\gameover.png");
    Gdiplus::Image image(L"C:\\Users\\shine\\Desktop\\Dev\\FlappyBird_WinAPI\\Assets\\gameover.png");
    graphics.DrawImage(&image, destRect);
}


void Scene::DrawBackground(HDC &memDC, RECT windowRect) {

    int width = windowRect.right - windowRect.left;
    int height = windowRect.bottom - windowRect.top;
    Gdiplus::Rect destRect(0, 0, width, height);
    Gdiplus::Graphics graphics(memDC);
    Gdiplus::Image image(backgroundType);
    graphics.DrawImage(&image, destRect);
    //    WCHAR * imageName = new WCHAR[255];
//    wcscpy(imageName, L"C:\\Users\\shine\\Desktop\\Dev\\FlappyBird_WinAPI\\Assets\\background-night.png");
//    Draw(destRect, memDC, imageName);
}

void Scene::Draw(Gdiplus::Rect destRect, HDC &memDC, WCHAR * imageName) {
    Gdiplus::Graphics graphics(memDC);
    Gdiplus::Image image(imageName);
    graphics.DrawImage(&image, destRect);
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
    pipe.ResetCounter();
    pipe.StopCounting();
}

void Scene::KeyAnalyse(HWND hWnd, WPARAM wParam, RECT windowRect) {
    // 0x30 - 0 ... 0x39 - 9
    switch (wParam) {
        case 0x31: {
            coins -= shop.BuyItem(1, coins);
            break;
        }
        case 0x32: {
            coins -= shop.BuyItem(2, coins);
            break;
        }
        case 0x33: {
            coins -= shop.BuyItem(3, coins);
            break;
        }
        case 0x34: {
            coins -= shop.BuyItem(4, coins);
            break;
        }
        case 0x35: {
            coins -= shop.BuyItem(5, coins);
            break;
        }
        case 0x36: {
            coins -= shop.BuyItem(6, coins);
            break;
        }
        case 0x37: {
            coins -= shop.BuyItem(7, coins);
            break;
        }
        case 0x38: {
            coins -= shop.BuyItem(8, coins);
            break;
        }
        case 0x39: {
            coins -= shop.BuyItem(9, coins);
            break;
        }
    }
}

void Scene::SetNewBackground(WCHAR * backgroundName) {
    WCHAR * wchar = Helper::GetWCHAR(Helper::GetAssetsDir());
    wcscat(wchar, backgroundName);
    wcscpy(backgroundType, wchar);
}
