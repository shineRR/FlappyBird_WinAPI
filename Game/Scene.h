//
// Created by shine on 11/3/2020.
//

#ifndef FLAPPYBIRD_WINAPI_SCENE_H
#define FLAPPYBIRD_WINAPI_SCENE_H

#define GetCurrentDir _getcwd
#include <string>
#include <dirent.h>
#include "windows.h"
#include "GameState.h"
#include "../Bird/Bird.h"
#include "../Pipe/Pipe.h"
#include <iostream>

class Scene {
    public:
        explicit Scene(GameState* _state, Bird* _bird, HWND* hWnd);
        Scene();
        BOOL isActive = false;
        Pipe pipe = Pipe(L"C:\\Users\\shine\\Desktop\\Dev\\FlappyBird_WinAPI\\Assets\\pipe-red.png");
        void Render(HWND hWnd);
        void MovePipe();
        void UpdatePipePosition();

    void UpdatePipePosition(RECT windowRect);

private:
        GameState* state;
        Bird* bird;
        static std::string GetAssetsDir();
        void DrawStartMenu(HDC &memDC, RECT windowRect);
        void DrawFloor(HDC &memDC, RECT windowRect);
        void DrawBackground(HDC &memDC, RECT windowRect);
};


#endif //FLAPPYBIRD_WINAPI_SCENE_H
