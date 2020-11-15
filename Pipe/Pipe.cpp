//
// Created by shine on 11/7/2020.
//

#include "Pipe.h"

Pipe::Pipe(const WCHAR* _pipeType, int coins) {
    _coins = coins;
    srand((unsigned int)time(nullptr));
    wcscpy(pipeType, _pipeType);
    InitializePipes(pipes, true);
    InitializePipes(nextPipes, false);
    RECT rect = {0, 0, DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT};
    updatePipesPosition(rect, pipes, DEFAULT_WINDOW_WIDTH, true);
}

void Pipe::InitializePipes(PipeItem (&pipeItem)[PIPES][COUPLE], bool genCoin) {
    for (int i = 0; i < PIPES; ++i) {
        for (int j = 0; j < COUPLE; ++j) {
            pipeItem[i][j].x = 0;
            pipeItem[i][j].y = 0 ;
            pipeItem[i][j].width = 0;
            pipeItem[i][j].height = 0;
            pipeItem[i][j].offsetX = 0;
            pipeItem[i][j].distanceFromFirstPipe = 0;
            pipeItem[i][j].offsetY = 0;
            pipeItem[i][j].hasCoin = (genCoin && j == 0) && randCoin();
            pipeItem[i][j].passed = false;
        }
    }
}

int * Pipe::GenerateHeightForCouplePipes(int windowHeight, int *pipesHeight) {
    pipesHeight[0] = rand() % (windowHeight - 100);
    pipesHeight[1] = windowHeight - pipesHeight[0];
}

void Pipe::updatePipesPosition(RECT windowRect, PipeItem (&pipeItem)[PIPES][COUPLE], int initialPx, BOOL generate) {
    GetCoefs(windowRect);
    const int distanceBetweenPipesX = int(280 * coefX);
    const int distanceBetweenPipesY = int(120 * coefY);

    int distanceFromFirstPipe = 0;
    int windowHeight = windowRect.bottom - windowRect.top;
    for (int i = 0; i < PIPES; ++i) {
        int offsetY = 0;

        int pipesHeight[2] = {0, 0};
        if (generate)
            GenerateHeightForCouplePipes(windowHeight, pipesHeight);

        for (int j = 0; j < COUPLE; ++j) {
            pipeItem[i][j].x -= pipeItem[i][j].offsetX + pipeItem[i][j].distanceFromFirstPipe ;
            int offsetX = int(pipeItem[i][j].x * coefX) - pipeItem[i][j].x;
            pipeItem[i][j].x = pipeItem[i][j].x + offsetX + distanceFromFirstPipe + initialPx;
            pipeItem[i][j].offsetX = offsetX;
            pipeItem[i][j].distanceFromFirstPipe = distanceFromFirstPipe;
            pipeItem[i][j].y = 0 + offsetY;
            pipeItem[i][j].width = int(pipeWidth * coefX);
            pipeItem[i][j].height -= pipeItem[i][j].offsetY;
            int additionalY = int(pipeItem[i][j].height * coefY) - pipeItem[i][j].height;
            pipeItem[i][j].height = generate ? pipesHeight[j] : pipeItem[i][j].height + additionalY;
            pipeItem[i][j].offsetY = additionalY;

            offsetY += pipeItem[i][j].height + distanceBetweenPipesY;
        }
        distanceFromFirstPipe += distanceBetweenPipesX;
    }
}

bool Pipe::DrawPipes(HDC &memDC, POINTL birdPoint) {
    Gdiplus::Graphics graphics(memDC);
    bool collision = false;
    for (int i = 0; i < PIPES; ++i) {
        if (!pipes[i][0].passed && (!pipes[0][0].passed || pipes[i-1][0].passed) && CollisionCheck(birdPoint, i))
            collision = true;
        CollectCoin(birdPoint, i);
        DrawCoin(graphics, i);
        IncTraveledDistance(birdPoint, i);
        for (int j = 0; j < COUPLE; ++j) {
            Gdiplus::Rect destRect(pipes[i][j].x, pipes[i][j].y, pipes[i][j].width, pipes[i][j].height);
            Gdiplus::Image image(pipeType);
            if (j == 0) {
                image.RotateFlip(Gdiplus::Rotate180FlipX);
            }
            graphics.DrawImage(&image, destRect);
        }
    }
    DrawCollectedCoins(graphics, _coins);
    DrawTraveledDistance(graphics);
    return collision;
}

void Pipe::DrawCollectedCoins(Gdiplus::Graphics &graphics, int coins) {
    std::string text("Coins: ");
    Gdiplus::RectF  rectF(15.0f, 10.0f, 100.0f, 100.0f);
    text += std::to_string(_coins);
    DrawTextZ(graphics, text, rectF);
}

void Pipe::DrawTraveledDistance(Gdiplus::Graphics &graphics) {
    std::string text("Traveled Distance: ");
    Gdiplus::RectF  rectF(15.0f, 40.0f, 300.0f, 100.0f);
    text += std::to_string(traveledDistance);
    DrawTextZ(graphics, text, rectF);
}

void Pipe::DrawTextZ(Gdiplus::Graphics &graphics, std::string text, Gdiplus::RectF rectF) {
    std::wstring wide_string = std::wstring(text.begin(), text.end());
    const wchar_t* result = wide_string.c_str();
    WCHAR wchar[255];
    wcscpy(wchar, result);
    Gdiplus::FontFamily   fontFamily(L"Arial");
    Gdiplus::Font         font(&fontFamily, 12, Gdiplus::FontStyleBold, Gdiplus::UnitPoint);
    Gdiplus::SolidBrush   solidBrush(Gdiplus::Color(255, 255, 255, 255));
    graphics.DrawString(wchar, -1, &font, rectF, NULL, &solidBrush);
}

bool Pipe::CollisionCheck(POINTL birdPoint, int i) {
    int pipeX = pipes[i][0].x;
    int upperHeight = pipes[i][0].height;
    const int distanceBetweenPipesY = int(120 * coefY);
    int lowerHeight = upperHeight + distanceBetweenPipesY;
    if(birdPoint.x >= pipeX && (birdPoint.y <= upperHeight || birdPoint.y >= lowerHeight))
        return true;
    return false;
}

void Pipe::IncTraveledDistance(POINTL birdPoint, int i) {
    int pipePos = pipes[i][0].x + pipes[i][0].width * coefX;
    if(!pipes[i][0].passed && pipePos <= birdPoint.x)
    {
        pipes[i][0].passed = true;
        pipes[i][1].passed = true;
        traveledDistance++;
    }
}


void Pipe::CollectCoin(POINTL birdPoint, int i) {
    int pipePos = pipes[i][0].x + 20 * coefX;
    if(pipes[i][0].hasCoin && pipePos <= birdPoint.x)
    {
        pipes[i][0].hasCoin = false;
        _coins++;
    }
}

void Pipe::DrawCoin(Gdiplus::Graphics &graphics, int i) {
    if(pipes[i][0].hasCoin) {
        int x = pipes[i][0].x + int(20 * coefX);
        int y = pipes[i][0].height + int(40 * coefY);
        int width = int(40 * coefX);
        int height = int(40 * coefY);
        Gdiplus::Rect rectForCoin(x, y, width, height);
        Gdiplus::Image coinImg(L"C:\\Users\\shine\\Desktop\\Dev\\FlappyBird_WinAPI\\Assets\\coin.png");
        graphics.DrawImage(&coinImg, rectForCoin);
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
    if (pipes[MIDDLE][1].x <= 0) {
        GenerateNextPipes(windowRect);
    }
}

void Pipe::GenerateNextPipes(RECT windowRect) {

    int initialPx = pipes[PIPES - 1][0].x + pipes[PIPES - 1][0].width + 200 * coefX;
    InitializePipes(nextPipes, true);
    updatePipesPosition(windowRect, nextPipes, initialPx, true);

    const int distance = nextPipes[2][0].distanceFromFirstPipe - nextPipes[1][0].distanceFromFirstPipe;
    PipeItem tempPipes[PIPES][COUPLE];

    int distanceFromFirstPipe = 0;
    for (int i = 0; i < MIDDLE; ++i) {
        for (int j = 0; j < COUPLE; ++j) {
            tempPipes[i][j] = pipes[MIDDLE + i][j];    // 0...4
            tempPipes[i][j].distanceFromFirstPipe = distanceFromFirstPipe;
        }
        distanceFromFirstPipe += distance;
    }

    for (int i = MIDDLE; i < PIPES; ++i) {
        for (int j = 0; j < COUPLE; ++j) {
            tempPipes[i][j] = nextPipes[i - MIDDLE][j];  // 5...9
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

bool Pipe::randCoin() {
    int value = rand() % 100;
    return value % 4 == 0;
}

int Pipe::ResetCounter() const {
    return _coins;
}

void Pipe::StopCounting() {
    traveledDistance = 0;
}

int Pipe::GetTraveledDistance() const {
    return traveledDistance;
}
