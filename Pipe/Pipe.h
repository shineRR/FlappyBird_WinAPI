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

#define DEFAULT_WINDOW_WIDTH 1280
#define DEFAULT_WINDOW_HEIGHT 720
#define PIPES 10
#define COUPLE 2

struct PipeItem {
    int x;
    int y;
    int width;
    int height;
    int offsetX;
    int distanceFromFirstPipe;
    int offsetY;
};

class Pipe {
    private:
        const int pipeWidth = 80;
        PipeItem pipes[PIPES][COUPLE];
        WCHAR pipeType[255];
        double coefX = 1;
        void InitializePipes();
        static int * GenerateHeightForCouplePipes(int windowHeight, int *pipesHeight);
    public:
        double coefY = 1;
        explicit Pipe(const WCHAR* _pipeType);
        void DrawPipes(HDC &memDC);
        void PrintPipes();
        void Movement();
        void GetCoefs(RECT rect);
        void updatePipesPosition(RECT windowRect, int initialPx, BOOL generate);
};


#endif //FLAPPYBIRD_WINAPI_PIPE_H
