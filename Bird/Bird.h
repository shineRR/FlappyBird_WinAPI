//
// Created by shine on 11/3/2020.
//

#ifndef FLAPPYBIRD_WINAPI_BIRD_H
#define FLAPPYBIRD_WINAPI_BIRD_H

#define DEFAULT_WINDOW_WIDTH 800
#define DEFAULT_WINDOW_HEIGHT 600

#include "windows.h"
#include <iostream>
#include <gdiplus.h>
#include <cwchar>

class Bird {
    private:
        const int birdWidth = 25;
        const int birdHeight = 25;
        int moveDistance = 10;
        WCHAR bird[255];
        void ValidatePosition(RECT windowRect, double multiplierDirection);
    public:
        int x;
        int y;
        explicit Bird(const WCHAR* _bird);
        void DrawBird(HDC &memDC);
        void UpdateXY(int _x, int _y);
        void MoveVertical(RECT windowRect, double multiplierDirection);
        void UpdateMoveDistance(double windowWidth, double windowHeight);
};


#endif //FLAPPYBIRD_WINAPI_BIRD_H
