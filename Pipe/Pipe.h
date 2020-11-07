//
// Created by shine on 11/7/2020.
//

#ifndef FLAPPYBIRD_WINAPI_PIPE_H
#define FLAPPYBIRD_WINAPI_PIPE_H

#define DEFAULT_WINDOW_WIDTH 800
#define DEFAULT_WINDOW_HEIGHT 600

#include "windows.h"
#include <iostream>
#include <gdiplus.h>
#include <cwchar>
#include <cstring>

struct PipeItem {
    int x;
    int y;
    int width;
    int height;
};

class Pipe {
    private:
        const int pipeWidth = 80;
        PipeItem pipes[20][2];
        WCHAR pipeType[255];
        double coefX = 1;
        double coefY = 1;
    public:
        explicit Pipe(const WCHAR* _pipeType);
        void GeneratePipes(RECT windowRect);
        void DrawPipes(HDC &memDC);
        void PrintPipes();
        void Movement();
        void updatePipesPosition(RECT rect);
        void GetCoefs(RECT rect);
};


#endif //FLAPPYBIRD_WINAPI_PIPE_H
