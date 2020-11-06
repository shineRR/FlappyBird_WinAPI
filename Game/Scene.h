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
#include <iostream>

class Scene {
    public:
        explicit Scene(GameState* _state);
        Scene();
        void Render(HWND hWnd);
    private:
        GameState* state;
        static std::string GetAssetsDir();
        void DrawStartMenu(HDC &memDC, RECT windowRect);
        void DrawFloor(HDC &memDC, RECT windowRect);
        void DrawBackground(HDC &memDC, RECT windowRect);
};


#endif //FLAPPYBIRD_WINAPI_SCENE_H
