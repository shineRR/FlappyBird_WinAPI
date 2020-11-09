//
// Created by shine on 11/7/2020.
//

#include "Pipe.h"

Pipe::Pipe(const WCHAR* _pipeType) {
    srand((unsigned int)time(nullptr));
    wcscpy(pipeType, _pipeType);
    InitializePipes(pipes);
    InitializePipes(nextPipes);
    RECT rect = {0, 0, DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT};
    updatePipesPosition(rect, pipes, DEFAULT_WINDOW_WIDTH, true);
}

void Pipe::InitializePipes(PipeItem (&pipeItem)[PIPES][COUPLE]) {
    for (int i = 0; i < PIPES; ++i) {
        for (int j = 0; j < COUPLE; ++j) {
            pipeItem[i][j].x = 0;
            pipeItem[i][j].y = 0 ;
            pipeItem[i][j].width = 0;
            pipeItem[i][j].height = 0;
            pipeItem[i][j].offsetX = 0;
            pipeItem[i][j].distanceFromFirstPipe = 0;
            pipeItem[i][j].offsetY = 0;
        }
    }
}

int * Pipe::GenerateHeightForCouplePipes(int windowHeight, int *pipesHeight) {
    pipesHeight[0] = rand() % (windowHeight - 100);
    pipesHeight[1] = windowHeight - pipesHeight[0];
}

void Pipe::updatePipesPosition(RECT windowRect, PipeItem (&pipeItem)[PIPES][COUPLE], int initialPx, BOOL generate) {
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
            pipeItem[i][j].x -= pipeItem[i][j].offsetX + pipeItem[i][j].distanceFromFirstPipe ;
            int offsetX = pipeItem[i][j].x * coefX - pipeItem[i][j].x;
            pipeItem[i][j].x = pipeItem[i][j].x + offsetX + distanceFromFirstPipe + initialPx;
            pipeItem[i][j].offsetX = offsetX;
            pipeItem[i][j].distanceFromFirstPipe = distanceFromFirstPipe;
            pipeItem[i][j].y = 0 + offsetY;
            pipeItem[i][j].width = pipeWidth * coefX;
            pipeItem[i][j].height -= pipeItem[i][j].offsetY;
            int additionalY = pipeItem[i][j].height * coefY - pipeItem[i][j].height;
            pipeItem[i][j].height = generate ? pipesHeight[j] : pipeItem[i][j].height + additionalY;
            pipeItem[i][j].offsetY = additionalY;

            offsetY += pipeItem[i][j].height + distanceBetweenPipesY;
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
    for (int i = 0; i < PIPES; ++i) {
        for (int j = 0; j < COUPLE; ++j) {
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
            std::cout << "offsetX = ";
            std::cout << pipes[i][j].offsetX << std::endl;
            std::cout << "offsetY = ";
            std::cout << pipes[i][j].offsetY << std::endl;
            std::cout << "distanceFromFirstPipe = ";
            std::cout << pipes[i][j].distanceFromFirstPipe << std::endl;
        }
        std::cout << "_______________________________" << std::endl;
    }
}

void Pipe::ValidateMap(RECT windowRect) {
    if (pipes[5][1].x <= 0) {
        GenerateNextPipes(windowRect);
    }
}

void Pipe::GenerateNextPipes(RECT windowRect) {

    int initialPx = pipes[PIPES - 1][0].x + pipes[PIPES - 1][0].width + 200 * coefX;
    InitializePipes(nextPipes);
    updatePipesPosition(windowRect, nextPipes, initialPx, true);

    const int distance = nextPipes[2][0].distanceFromFirstPipe - nextPipes[1][0].distanceFromFirstPipe;
    PipeItem tempPipes[PIPES][COUPLE];

    int distanceFromFirstPipe = 0;
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < COUPLE; ++j) {
            tempPipes[i][j] = pipes[5 + i][j];    // 0...4
            tempPipes[i][j].distanceFromFirstPipe = distanceFromFirstPipe;
        }
        distanceFromFirstPipe += distance;
    }

    for (int i = 5; i < PIPES; ++i) {
        for (int j = 0; j < COUPLE; ++j) {
            tempPipes[i][j] = nextPipes[i - 5][j];  // 5...9
            tempPipes[i][j].distanceFromFirstPipe = distanceFromFirstPipe;
        }
        distanceFromFirstPipe += distance;
    }

    for (int i = 0; i < PIPES; ++i) {
        for (int j = 0; j < COUPLE; ++j) {
            pipes[i][j] = tempPipes[i][j];
        }
    }
}
