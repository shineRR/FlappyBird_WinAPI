//
// Created by shine on 11/3/2020.
//

#ifndef FLAPPYBIRD_WINAPI_BIRD_H
#define FLAPPYBIRD_WINAPI_BIRD_H

#include "windows.h"
#include <iostream>
#include <cstring>
#include <gdiplus.h>
#include <cwchar>
#include "winuser.h"

class Bird {
    private:
        const int birdWidth = 25;
        const int birdHeight = 25;
        int moveDistance = 10;
        WCHAR bird[255];
    public:
        int x;
        int y;
        explicit Bird(const WCHAR* _bird);
        void DrawBird(HDC &memDC);
        void UpdateXY(int _x, int _y);
        void MoveVertical(RECT windowRect, int multiplierDirection);
        void ValidatePosition(RECT windowRect, int multiplierDirection);
};


#endif //FLAPPYBIRD_WINAPI_BIRD_H
