//
// Created by shine on 11/3/2020.
//

#ifndef FLAPPYBIRD_WINAPI_GAME_H
#define FLAPPYBIRD_WINAPI_GAME_H

#include "algorithm"
#include "gdiplus.h"
#include "Scene.h"

class Game {
    public:
        static void Run(HWND hWnd);
        static void Quit();
};


#endif //FLAPPYBIRD_WINAPI_GAME_H
