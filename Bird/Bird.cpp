//
// Created by shine on 11/3/2020.
//

#include "Bird.h"

Bird::Bird(const WCHAR* _bird) {
    wcscpy(bird, _bird);
    x = 0;
    y = 0;
}

void Bird::DrawBird(HDC &memDC) {
    Gdiplus::Graphics graphics(memDC);
    Gdiplus::Rect destRect(x, y, birdWidth * coefX, birdHeight * coefY);
    Gdiplus::Image image(bird);
    graphics.DrawImage(&image, destRect);
}

void Bird::ValidatePosition(RECT windowRect, double multiplierDirection) {
    int moveDist = y + moveDistance * multiplierDirection;
    if (moveDist <= windowRect.top && multiplierDirection < 0 ||
            moveDist >= windowRect.bottom && multiplierDirection > 0) {
        return;
    }
    y = moveDist;
}

void Bird::UpdateXY(int _x, int _y) {
    x = _x;
    y = _y;
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