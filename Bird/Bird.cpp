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
    Gdiplus::Rect destRect(x, y, birdWidth, birdHeight);
    Gdiplus::Image image(bird);
    graphics.DrawImage(&image, destRect);
}

void Bird::ValidatePosition(RECT windowRect, int multiplierDirection) {
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

void Bird::MoveVertical(RECT windowRect, int multiplierDirection) {
    windowRect.bottom -= birdHeight;
    ValidatePosition(windowRect, multiplierDirection);
}

void Bird::UpdateMoveDistance(double windowWidth, double windowHeight) {
    int distance = 10;
    double coefX = windowHeight / DEFAULT_WINDOW_HEIGHT;
    distance *= coefX;
    moveDistance = distance;
}
