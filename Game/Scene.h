//
// Created by shine on 11/3/2020.
//

#ifndef FLAPPYBIRD_WINAPI_SCENE_H
#define FLAPPYBIRD_WINAPI_SCENE_H

#include <direct.h>
#define GetCurrentDir _getcwd
#include <string>
#include "gdiplus.h"
#include "windows.h"
#include <iostream>

class Scene {
    public:
        static void Start(HWND hWnd);
    private:
        static std::string GetAssetsDir();
        static void DrawStartMenu(HDC &memDC, RECT windowRect);
        static void DrawFloor(HDC &memDC, RECT windowRect);
        static void DrawBackground(HDC &memDC, RECT windowRect);
};


#endif //FLAPPYBIRD_WINAPI_SCENE_H
