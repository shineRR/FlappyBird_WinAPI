//
// Created by shine on 11/3/2020.
//

#ifndef FLAPPYBIRD_WINAPI_SCENE_H
#define FLAPPYBIRD_WINAPI_SCENE_H

#include <dirent.h>
#include "windows.h"
#include "../GameState.h"
#include "../../Bird/Bird.h"
#include "../../Pipe/Pipe.h"
#include "../Shop/Shop.h"
#include <iostream>

class Scene {
    public:
        Scene(GameState* _state, Bird* _bird);
        Scene();
        int coins = 100;
        BOOL isActive = false;
        Pipe pipe = Pipe(L"C:\\Users\\shine\\Desktop\\Dev\\FlappyBird_WinAPI\\Assets\\pipe-red.png", coins);
        void Render(HWND hWnd);
        void MovePipe(RECT windowRect);
        void UpdateObjectPositions(RECT windowRect);
        int ResetCounter();
        void KeyAnalyse(HWND hWnd, WPARAM wParam, RECT windowRect);

private:
        GameState* state;
        Bird* bird;
        int bestScore = 0;
        Shop shop = Shop();
        void DrawStartMenu(HDC &memDC, RECT windowRect);
        void DrawFloor(HDC &memDC, RECT windowRect);
        void DrawBackground(HDC &memDC, RECT windowRect);
        void DrawGameOver(HDC &memDC, RECT windowRect);
        void DrawScore(HDC &memDC, RECT windowRect);
        static void Draw(Gdiplus::Rect destRect, HDC &memDC, WCHAR * image);
};


#endif //FLAPPYBIRD_WINAPI_SCENE_H
