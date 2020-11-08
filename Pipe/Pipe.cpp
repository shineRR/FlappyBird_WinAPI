//
// Created by shine on 11/7/2020.
//

#include "Pipe.h"

Pipe::Pipe(const WCHAR* _pipeType) {
    wcscpy(pipeType, _pipeType);
    RECT rect = {0, 0, DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT};
    GeneratePipes(rect);
}

void Pipe::GeneratePipes(RECT windowRect) {
    const int distanceBetweenPipesX = 100;
    const int distanceBetweenPipesY = 120;
    int x = 0;
    int y = 0;
    int offsetX = 0;
    int pipeHeight = (DEFAULT_WINDOW_HEIGHT - distanceBetweenPipesY) / 2;
    for (int i = 0; i < sizeof(pipes)/sizeof(pipes[0]); ++i) {
        int offsetY = 0;
        for (int j = 0; j < 2; ++j) {
            pipes[i][j].x = DEFAULT_WINDOW_WIDTH + offsetX;
            pipes[i][j].y = 0 + offsetY;
            pipes[i][j].width = pipeWidth;
            pipes[i][j].height = pipeHeight;
            offsetY += pipeHeight + distanceBetweenPipesY;
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

void Pipe::updatePipesPosition(RECT rect) {
    std::cout << "updatePipesPosition" << std::endl;
    double width = rect.right - rect.left;
    double height = rect.bottom - rect.top;
//    double coefX = width / DEFAULT_WINDOW_WIDTH;
//    double coefY = height / DEFAULT_WINDOW_HEIGHT;

    const int distanceBetweenPipesX = 90 * coefX;
    const int distanceBetweenPipesY = 120 * coefY;
    int offsetX = 0;
    int pipeHeight = (height - distanceBetweenPipesY) / 2;
    for (int i = 0; i < sizeof(pipes)/sizeof(pipes[0]); ++i) {
        int offsetY = 0;
        for (int j = 0; j < 2; ++j) {
            pipes[i][j].x = pipes[i][j].x + offsetX;
            pipes[i][j].y = 0 + offsetY;
            pipes[i][j].width = pipeWidth * coefX;
            pipes[i][j].height = pipeHeight;
            offsetY += pipeHeight + distanceBetweenPipesY;
        }
        offsetX += distanceBetweenPipesX;
    }
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