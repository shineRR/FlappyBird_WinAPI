//
// Created by shine on 11/7/2020.
//

#ifndef FLAPPYBIRD_WINAPI_PIPE_H
#define FLAPPYBIRD_WINAPI_PIPE_H

#include "windows.h"
#include <iostream>
#include <gdiplus.h>
#include <ctime>
#include <cwchar>
#include <cstring>
#include <cstdlib>
#include "../Helper/Helper.h"

#define DEFAULT_WINDOW_WIDTH 1280
#define DEFAULT_WINDOW_HEIGHT 720
#define PIPES 16
#define COUPLE 2
#define MIDDLE 8

struct PipeItem {
    int x;
    int y;
    int width;
    int height;
    int offsetX;
    int distanceFromFirstPipe;
    int offsetY;
    bool hasCoin;
    bool passed;
};

class Pipe {
    private:
        const int pipeWidth = 80;
        PipeItem nextPipes[PIPES][COUPLE];
        int _coins = 0;
        int traveledDistance = 0;

        WCHAR pipeType[255];
        double coefX = 1;
        double coefY = 1;
        void GenerateNextPipes(RECT windowRect);
        void GetCoefs(RECT rect);
        static int * GenerateHeightForCouplePipes(int windowHeight, int *pipesHeight);
        static bool randCoin();
    public:
        PipeItem pipes[PIPES][COUPLE];
        explicit Pipe(const WCHAR* _pipeType);
        void CollectCoin(POINTL birdPoint, int i);
        bool CollisionCheck(POINTL birdPoint, int i);
        bool DrawPipes(HDC &memDC, POINTL birdPoint);
        void DrawCoin(Gdiplus::Graphics &graphics, int i);
        static void DrawCollectedCoins(Gdiplus::Graphics &graphics, std::string string, int coins);
        void DrawTraveledDistance(Gdiplus::Graphics &graphics) const;
        int GetTraveledDistance() const;
        void IncTraveledDistance(POINTL birdPoint, int i);
        static void InitializePipes(PipeItem (&pipeItem)[PIPES][COUPLE], bool genCoin);
        void Movement();
        void PrintPipes();
        int ResetCounter();
        void SetCoins(int coins);
        void SetNewPipe(WCHAR* name);
        void StopCounting();
        void ValidateMap(RECT windowRect);
        void updatePipesPosition(RECT windowRect, PipeItem (&pipeItem)[PIPES][COUPLE], int initialPx, BOOL generate);
};


#endif //FLAPPYBIRD_WINAPI_PIPE_H
