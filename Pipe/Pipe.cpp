//
// Created by shine on 11/7/2020.
//

#include "Pipe.h"

Pipe::Pipe(const WCHAR* _pipeType) {
    srand((unsigned int)time(nullptr));
    wcscpy(pipeType, _pipeType);
    InitializePipes();
    RECT rect = {0, 0, DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT};
    updatePipesPosition(rect, DEFAULT_WINDOW_WIDTH);
}

void Pipe::InitializePipes() {
    for (int i = 0; i < 20; ++i) {
        for (int j = 0; j < 2; ++j) {
            pipes[i][j].x = 0;
            pipes[i][j].y = 0 ;
            pipes[i][j].width = 0;
            pipes[i][j].height = 0;
        }
    }
}

int * Pipe::GenerateHeightForCouplePipes(int windowHeight, int *pipesHeight) {
//    int pipesHeight[2];=
//    int * array = pipesHeight;
    pipesHeight[0] = rand() % (windowHeight - 100);
    pipesHeight[1] = windowHeight - pipesHeight[0];
    std::cout << pipesHeight[0] << std::endl;
    std::cout << pipesHeight[1] << std::endl;
}

void Pipe::GeneratePipes(RECT windowRect) {
    const int distanceBetweenPipesX = 100;
    const int distanceBetweenPipesY = 120;
    int x = 0;
    int y = 0;
    int offsetX = 0;
    int windowHeight = windowRect.bottom - windowRect.top - distanceBetweenPipesY;
    for (int i = 0; i < sizeof(pipes)/sizeof(pipes[0]); ++i) {
        int offsetY = 0;
        int pipesHeight[2];
        GenerateHeightForCouplePipes(windowHeight, pipesHeight);
        for (int j = 0; j < 2; ++j) {
            pipes[i][j].x = DEFAULT_WINDOW_WIDTH + offsetX;
            pipes[i][j].y = 0 + offsetY;
            pipes[i][j].width = pipeWidth;
            pipes[i][j].height = pipesHeight[j];
            offsetY += pipesHeight[j] + distanceBetweenPipesY;
        }
        offsetX += distanceBetweenPipesX;
    }
}

void Pipe::updatePipesPosition(RECT windowRect, int initialPx) {
//    double coefX = width / DEFAULT_WINDOW_WIDTH;
//    double coefY = height / DEFAULT_WINDOW_HEIGHT;

    const int distanceBetweenPipesX = 90 * coefX;
    const int distanceBetweenPipesY = 120 * coefY;

    int offsetX = 0;
    int windowHeight = windowRect.bottom - windowRect.top - distanceBetweenPipesY;
    for (int i = 0; i < sizeof(pipes)/sizeof(pipes[0]); ++i) {
        int offsetY = 0;
        int pipesHeight[2];
        GenerateHeightForCouplePipes(windowHeight, pipesHeight);
        for (int j = 0; j < 2; ++j) {
            pipes[i][j].x = pipes[i][j].x + offsetX + initialPx;
            pipes[i][j].y = 0 + offsetY;
            pipes[i][j].width = pipeWidth * coefX;
            pipes[i][j].height = pipesHeight[j];
            offsetY += pipesHeight[j] + distanceBetweenPipesY;
        }
        offsetX += distanceBetweenPipesX;
    }
}

void Pipe::DrawPipes(HDC &memDC) {
    Gdiplus::Graphics graphics(memDC);
    for (int i = 0; i < 20; ++i) {
        for (int j = 0; j < 2; ++j) {
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
}

void Pipe::Movement() {
    for (int i = 0; i < 20; ++i) {
        for (int j = 0; j < 2; ++j) {
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
