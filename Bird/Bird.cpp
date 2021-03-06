//
// Created by shine on 11/3/2020.
//

#include "Bird.h"
#include "../Helper/Helper.h"

Bird::Bird(const WCHAR* _bird) {
    WCHAR * wchar = Helper::GetWCHAR(Helper::GetAssetsDir());
    wcscat(wchar, _bird);
    wcscpy(bird, wchar);
    x = 0;
    y = 0;
}

void Bird::DrawBird(HDC &memDC) {
    Gdiplus::Graphics graphics(memDC);
    Gdiplus::Rect destRect(x, y, birdWidth * coefX, birdHeight * coefY);
    Gdiplus::Image image(bird);
    graphics.DrawImage(&image, destRect);
}

POINTL Bird::GetPos() {
    POINTL point = {x, y};
    return point;
}

void Bird::ValidatePosition(RECT windowRect, double multiplierDirection) {
    int moveDist = y + moveDistance * multiplierDirection;
    if (moveDist <= windowRect.top && multiplierDirection < 0 ||
            moveDist >= windowRect.bottom && multiplierDirection > 0) {
        return;
    }
    y = moveDist;
}

void Bird::UpdateXY(RECT windowRect) {
    int width = (windowRect.right - windowRect.left);
    int height = (windowRect.bottom - windowRect.top);
    x =  width / 2 - 40;
    y = height / 2;
}

void Bird::MoveVertical(RECT windowRect, double multiplierDirection) {
    windowRect.bottom -= birdHeight;
    ValidatePosition(windowRect, multiplierDirection);
}

void Bird::UpdateMoveDistance(double windowWidth, double windowHeight) {
    int distance = 10;
    double coefX = windowHeight / DEFAULT_WINDOW_HEIGHT;
    distance *= coefX;
    moveDistance = distance;
}

void Bird::GetCoefs(RECT rect) {
    double width = rect.right - rect.left;
    double height = rect.bottom - rect.top;
    coefX = width / DEFAULT_WINDOW_WIDTH;
    coefY = height / DEFAULT_WINDOW_HEIGHT;
    if (coefY == 0) {
        coefX = 0.935;
        coefY = 0.935;
    }
}

void Bird::UpdateBirdPosition(RECT windowRect) {
    GetCoefs(windowRect);
    x -= offsetX;           // Return initial value
    y -= offsetY;
    offsetX = x * coefX - x;
    offsetY = y * coefY - y;
    x += offsetX;           // New value
    y += offsetY;
}

void Bird::SetNewBird(const WCHAR* name, int id) {
    wcscpy(bird, name);
    birdID = id;
}

int Bird::GetBirdID() const {
    return birdID;
}
