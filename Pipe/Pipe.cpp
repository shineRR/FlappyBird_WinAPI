//
// Created by shine on 11/7/2020.
//

#include "Pipe.h"

Pipe::Pipe(const WCHAR* _pipeType) {
    srand((unsigned int)time(nullptr));
    wcscpy(pipeType, _pipeType);
    InitializePipes();
    RECT rect = {0, 0, DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT};
    updatePipesPosition(rect, DEFAULT_WINDOW_WIDTH, true);
}

void Pipe::InitializePipes() {
    for (int i = 0; i < PIPES; ++i) {
        for (int j = 0; j < COUPLE; ++j) {
            pipes[i][j].x = 0;
            pipes[i][j].y = 0 ;
            pipes[i][j].width = 0;
            pipes[i][j].height = 0;
            pipes[i][j].offsetX = 0;
            pipes[i][j].distanceFromFirstPipe = 0;
            pipes[i][j].offsetY = 0;
        }
    }
}

int * Pipe::GenerateHeightForCouplePipes(int windowHeight, int *pipesHeight) {
    pipesHeight[0] = rand() % (windowHeight - 100);
    pipesHeight[1] = windowHeight - pipesHeight[0];
}

void Pipe::updatePipesPosition(RECT windowRect, int initialPx, BOOL generate) {
    GetCoefs(windowRect);
    const int distanceBetweenPipesX = 280 * coefX;
    const int distanceBetweenPipesY = 120 * coefY;

    int distanceFromFirstPipe = 0;
    int windowHeight = windowRect.bottom - windowRect.top;
    for (int i = 0; i < PIPES; ++i) {
        int offsetY = 0;

        int pipesHeight[2] = {0, 0};
        if (generate)
            GenerateHeightForCouplePipes(windowHeight, pipesHeight);

        for (int j = 0; j < COUPLE; ++j) {
            pipes[i][j].x -= pipes[i][j].offsetX + pipes[i][j].distanceFromFirstPipe ;
            int offsetX = pipes[i][j].x * coefX - pipes[i][j].x;
            pipes[i][j].x = pipes[i][j].x + offsetX + distanceFromFirstPipe + initialPx;
            pipes[i][j].offsetX = offsetX;
            pipes[i][j].distanceFromFirstPipe = distanceFromFirstPipe;
            pipes[i][j].y = 0 + offsetY;
            pipes[i][j].width = pipeWidth * coefX;
            pipes[i][j].height -= pipes[i][j].offsetY;
            int additionalY = pipes[i][j].height * coefY - pipes[i][j].height;
            pipes[i][j].height = generate ? pipesHeight[j] : pipes[i][j].height + additionalY;
            pipes[i][j].offsetY = additionalY;

            offsetY += pipes[i][j].height + distanceBetweenPipesY;
        }
        distanceFromFirstPipe += distanceBetweenPipesX;
    }
}

void Pipe::DrawPipes(HDC &memDC) {
    Gdiplus::Graphics graphics(memDC);
    for (int i = 0; i < PIPES; ++i) {
        for (int j = 0; j < COUPLE; ++j) {
            Gdiplus::Rect destRect(pipes[i][j].x, pipes[i][j].y, pipes[i][j].width, pipes[i][j].height);
            Gdiplus::Image image(pipeType);
            if (j == 0) {
                image.RotateFlip(Gdiplus::Rotate180FlipX);
            }
            graphics.DrawImage(&image, destRect);
        }
    }
}

void Pipe::GetCoefs(RECT rect) {
    double width = rect.right - rect.left;
    double height = rect.bottom - rect.top;
    coefX = width / DEFAULT_WINDOW_WIDTH;
    coefY = height / DEFAULT_WINDOW_HEIGHT;
    if (coefY == 0) {
        coefX = 0.935;
        coefY = 0.935;
    }
}

void Pipe::Movement() {
    for (int i = 0; i < PIPES; ++i) {
        for (int j = 0; j < COUPLE; ++j) {
            pipes[i][j].x -= 4;
        }
    }
}

void Pipe::PrintPipes() {
    for (int i = 0; i < 20; ++i) {
        for (int j = 0; j < 2; ++j) {
            std::cout << "pipe = ";
            std::cout << i;
            std::cout << " ";
            std::cout << j << std::endl;


            std::cout << "x = ";
            std::cout << pipes[i][j].x << std::endl;
            std::cout << "y = ";
            std::cout << pipes[i][j].y << std::endl;
            std::cout << "width = ";
            std::cout << pipes[i][j].width << std::endl;
            std::cout << "height = ";
            std::cout << pipes[i][j].height << std::endl;
        }
    }
}
