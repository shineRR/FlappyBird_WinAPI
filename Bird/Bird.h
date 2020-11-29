//
// Created by shine on 11/3/2020.
//

#ifndef FLAPPYBIRD_WINAPI_BIRD_H
#define FLAPPYBIRD_WINAPI_BIRD_H

#define DEFAULT_WINDOW_WIDTH 1280
#define DEFAULT_WINDOW_HEIGHT 720

#include "windows.h"
#include <iostream>
#include <gdiplus.h>
#include <cwchar>

class Bird {
    private:
        const int birdWidth = 25;
        const int birdHeight = 25;
        WCHAR bird[255];
        int birdID = 0;
        double coefX = 1;
        double coefY = 1;
        int x = 0;
        int y = 0;
        int offsetX = 0;
        int offsetY = 0;
        int moveDistance = 10;
        void ValidatePosition(RECT windowRect, double multiplierDirection);
    public:
        explicit Bird(const WCHAR* _bird);
        void DrawBird(HDC &memDC);
        void MoveVertical(RECT windowRect, double multiplierDirection);
        void UpdateMoveDistance(double windowWidth, double windowHeight);
        int GetBirdID() const;
        void GetCoefs(RECT rect);
        void UpdateBirdPosition(RECT windowRect);
        void UpdateXY(RECT windowRect);
        void SetNewBird(const WCHAR* name, int id);
        POINTL GetPos();
};


#endif //FLAPPYBIRD_WINAPI_BIRD_H
